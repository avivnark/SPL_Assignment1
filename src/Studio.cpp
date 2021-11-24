#include "../include/Studio.h"
#include <iostream>
#include <fstream>
#include "map"
#include "string"

using namespace std;

Studio::Studio() {
    open = true;
    sequentialCustomerId = 0;
}

Studio::Studio(const Studio &other) : open(other.open), sequentialCustomerId(other.sequentialCustomerId),
                                      workout_options(other.workout_options) { // Copy constructor
    trainers.reserve(other.trainers.size());
    actionsLog.reserve(other.actionsLog.size());

    for (auto *trainer: other.trainers) {
        trainers.push_back(new Trainer(*trainer));
    }
    for (auto *otherBaseAction: other.actionsLog) {
        actionsLog.push_back(otherBaseAction->clone());
    }
}


Studio::~Studio() { // Destructor
    clearStudioResources();
}


Studio::Studio(Studio &&other) : open(other.open),
                                 sequentialCustomerId(other.sequentialCustomerId) { // move constructor
    clearStudioResources();
    workout_options.clear();

    //move resources from other
    for (auto *trainer: other.trainers) {
        trainers.push_back(trainer);
    }
    for (auto *baseAction: other.actionsLog) {
        actionsLog.push_back(baseAction);
    }
    for (const auto &workout: other.workout_options) {
        workout_options.emplace_back(Workout(workout));
    }

    //delete other pointers
    other.trainers.clear();
    other.actionsLog.clear();
}

Studio &Studio::operator=(const Studio &other) { // copy assignment operator
    if (this != &other) {
        open = other.open;
        sequentialCustomerId = other.sequentialCustomerId;


        // clear current resources:
        clearStudioResources();
        workout_options.clear();

        //copy new studio into this
//        workout_options.assign(other.workout_options.begin(), other.workout_options.end());
        for (auto *trainer: other.trainers) {
            trainers.push_back(new Trainer(*trainer));
        }
        for (auto *baseAction: other.actionsLog) {
            actionsLog.push_back(baseAction->clone());
        }
        for (const auto &workout: other.workout_options) {
            workout_options.emplace_back(Workout(workout));
        }
    }
    return *this;
}

Studio &Studio::operator=(Studio &&other) { // move assignment operator
    if (this != &other) {
        clearStudioResources();
        workout_options.clear();
        trainers = std::move(other.trainers);
        actionsLog = std::move(other.actionsLog);
        for (auto workout: other.workout_options) {
            workout_options.emplace_back(Workout(workout));
        }
    }
    return *this;
}

Studio::Studio(const string &configFilePath) {
    open = true;
    sequentialCustomerId = 0;
    string line;
    ifstream MyReadFile(configFilePath);
    do {
        getline(MyReadFile, line);
    } while (line[0] == '\0' || line[0] == '#');
    unsigned int numOfTrainers = readNumOfTrainers(line);
    trainers.reserve(numOfTrainers);
    do {
        getline(MyReadFile, line);
    } while (line[0] == '\0' || line[0] == '#');
    createNewTrainers(line);
    int w_id = 0;
    while (getline(MyReadFile, line)) {
        // line example: Yoga, Anaerobic, 90
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }
        string w_name;
        WorkoutType w_type;
        int w_price;
        getWorkoutData(line, &w_name, &w_type, &w_price);
        workout_options.emplace_back(w_id, w_name, w_price, w_type);
        w_id++;
    }
    MyReadFile.close();
}

void Studio::start() {
    std::cout << "Studio is now Open!" << std::endl;
    string user_input;
    getline(cin, user_input);
    while (true) {
        string command;
        std::vector<string> args;
        extractCommand(user_input, command, args);
        if (command == "closeall") {
            auto *closeAll = new CloseAll();
            closeAll->act(*this);
            open = false;
            actionsLog.push_back(closeAll);
            break;
        } else if (command == "open") {
            int trainerId = stoi(args[0]);
            std::vector<Customer *> customerList;
            vector<string> customersRawInput({args.begin() + 1, args.end()});
            createCustomers(customersRawInput, customerList);
            auto *openTrainer = new OpenTrainer(trainerId, customerList);
            openTrainer->act(*this);
            customerList.clear();
            actionsLog.push_back(openTrainer);
        } else if (command == "close") {
            int trainerId = stoi(args[0]);
            auto *closeAction = new Close(trainerId);
            closeAction->act(*this);
            actionsLog.push_back(closeAction);
        } else if (command == "order") {
            int trainerId = stoi(args[0]);
            auto *orderAction = new Order(trainerId);
            orderAction->act(*this);
            actionsLog.push_back(orderAction);
        } else if (command == "move") {
            int origin_trainer_id = stoi(args[0]);
            int dest_trainer_id = stoi(args[1]);
            int customer_id = stoi(args[2]);
            auto *moveCustomer = new MoveCustomer(origin_trainer_id, dest_trainer_id, customer_id);
            moveCustomer->act(*this);
            actionsLog.push_back(moveCustomer);
        } else if (command == "workout_options") {
            auto *workoutOptions = new PrintWorkoutOptions();
            workoutOptions->act(*this);
            actionsLog.push_back(workoutOptions);
        } else if (command == "status") {
            int trainerId = stoi(args[0]);
            auto *printTrainerStatus = new PrintTrainerStatus(trainerId);
            printTrainerStatus->act(*this);
            actionsLog.push_back(printTrainerStatus);
        } else if (command == "log") {
            auto *printActionsLog = new PrintActionsLog();
            printActionsLog->act(*this);
            actionsLog.push_back(printActionsLog);
        } else if (command == "backup") {
            auto *backupStudio = new BackupStudio();
            actionsLog.push_back(backupStudio);
            backupStudio->act(*this);
        } else if (command == "restore") {
            auto *restoreStudio = new RestoreStudio();
            restoreStudio->act(*this);
            actionsLog.push_back(restoreStudio);
        } else {
            cout << "Unidentified command, please try again:" << endl;
        }
        getline(cin, user_input);
    }
}

int Studio::getNumOfTrainers() const {
    return (int) trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    if ((int) trainers.size() < tid) {
        return nullptr;
    }
    return trainers[tid];
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

int Studio::readNumOfTrainers(const string &line) {
    return stoi(line);
}

void Studio::createNewTrainers(string line) {
    //example input: "6,6,8,4"
    for (int i = 0; i < (int) line.length(); i += 2) {
        int capacity = line[i] - '0';
        trainers.push_back(new Trainer(capacity));
    }
}

void Studio::getWorkoutData(const std::string &line, string *w_name, WorkoutType *w_type, int *w_price) {
    //example line: Yoga, Anaerobic, 90
    unsigned long start_sep = 0;
    unsigned long end_sep = line.find(',');
    *w_name = line.substr(start_sep, end_sep);
    start_sep = end_sep + 2;
    end_sep = line.find(',', start_sep);
    *w_type = convertStringToEnum(line.substr(start_sep, end_sep - start_sep));
    start_sep = end_sep + 1;
    end_sep = line.length();
    *w_price = stoi(line.substr(start_sep, end_sep));
}

WorkoutType Studio::convertStringToEnum(const std::string &string_workout) {
    map<string, WorkoutType> type_map = {
            {"Mixed",     MIXED},
            {"Anaerobic", ANAEROBIC},
            {"Cardio",    CARDIO}
    };
    return type_map[string_workout];
}

std::string Studio::convertEnumToString(WorkoutType enum_workout) {
    map<WorkoutType, string> type_map = {
            {MIXED,     "Mixed"},
            {ANAEROBIC, "Anaerobic"},
            {CARDIO,    "Cardio"}
    };
    return type_map[enum_workout];
}

bool Studio::extractCommand(const string &user_input, string &command, vector<string> &args) {
    unsigned long start_sep = 0;
    unsigned long end_sep = user_input.find(' ');
    command = user_input.substr(start_sep, end_sep);
    start_sep = end_sep + 1;
    end_sep = user_input.find(' ', start_sep);
    while (start_sep != 0) {
        string arg = user_input.substr(start_sep, end_sep - start_sep);
        args.push_back(arg);
        start_sep = end_sep + 1;
        end_sep = user_input.find(' ', start_sep);
    }
    return true;

}

void Studio::createCustomers(vector<string> &args, vector<Customer *> &customerList) {
    // example args: ["Shalom,swt", "Dan,chp", "Alice,mcl", "Bob,fbd"]
    for (auto customerString: args) {
        string name, strategy;
        splitNameStrategy(customerString, name, strategy);
        if (strategy == "swt") {
            customerList.push_back(new SweatyCustomer(name, sequentialCustomerId));
        } else if (strategy == "chp") {
            customerList.push_back(new CheapCustomer(name, sequentialCustomerId));
        } else if (strategy == "mcl") {
            customerList.push_back(new HeavyMuscleCustomer(name, sequentialCustomerId));
        } else if (strategy == "fbd") {
            customerList.push_back(new FullBodyCustomer(name, sequentialCustomerId));
        }
        sequentialCustomerId++;
    }
}

void Studio::splitNameStrategy(string &customerString, string &name, string &strategy) {
    //example input for customerString: "Shalom,swt"
    int comma = customerString.find(',');
    name = customerString.substr(0, comma);
    strategy = customerString.substr(comma + 1);
}

void Studio::clearStudioResources() {
    for (auto *trainer: trainers) {
        delete trainer;
    }
    for (auto *baseAction: actionsLog) {
        delete baseAction;
    }
    trainers.clear();
    actionsLog.clear();
}
