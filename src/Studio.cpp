#include <iostream>
#include <fstream>
#include "map"
#include "string"
#include "../include/Studio.h"

using namespace std;

void Studio::start() {
    std::cout << "Studio is now Open!" << std::endl;
    string user_input;
    getline(cin, user_input);
    while (user_input != "closeall") {
        string command;
        std::vector<string> args;
        bool valid = extractCommand(user_input, command, args);
        if (command == "open"){
            int trainerId = stoi(args[0]);
            std::vector<Customer*> * customerList;
            vector<string> customersRawInput = {args.begin() + 1, args.end()};
            createCustomers(customersRawInput,*customerList);
            auto * openTrainer = new OpenTrainer(trainerId, *customerList);
            openTrainer->act(*this);
        } else if (command == "close"){
            int trainerId = stoi(args[0]);
            auto * closeAction = new Close(trainerId);
            closeAction->act(*this);
        }
        else if (command == "order"){
            int trainerId = stoi(args[0]);
            auto * orderAction = new Order(trainerId);
            orderAction->act(*this);
        }
        else if (command == "move"){
            int origin_trainer_id = stoi(args[0]);
            int dest_trainer_id = stoi(args[1]);
            int customer_id = stoi(args[2]);
            auto * moveCustomer = new MoveCustomer(origin_trainer_id, dest_trainer_id, customer_id);
            moveCustomer->act(*this);
        }
        else if (command == "workout_options"){
            auto * workoutOptions = new PrintWorkoutOptions();
            workoutOptions->act(*this);
        }
        else if (command == "status"){
            int trainerId = stoi(args[0]);
            auto * printTrainerStatus = new PrintTrainerStatus(trainerId);
            printTrainerStatus->act(*this);
        }
        else if (command == "log") {
            auto * printActionsLog = new PrintActionsLog();
            printActionsLog->act(*this);
        }
        else if (command == "backup"){
            BackupStudio * backupStudio = new BackupStudio();
            backupStudio->act(*this);
        } else{
            cout << "Unidentified command, please try again:" << endl;
        }
        getline(cin, user_input);
    }
}

Studio::Studio() {
    open = true;
}

Studio::Studio(const string &configFilePath) {
    open = true;
    string line;
    ifstream MyReadFile(configFilePath);
    getline(MyReadFile, line);
    int numOfTrainers = readNumOfTrainers(line);
    trainers.reserve(numOfTrainers);
    getline(MyReadFile, line);
    createNewTrainers(line);
    int w_id= 0;
    while (getline(MyReadFile, line)) {
        // line example: Yoga, Anaerobic, 90
        if (line.empty()){
            continue;
        }
        string w_name;
        WorkoutType w_type;
        int w_price;
        getWorkoutData(line, &w_name, &w_type, &w_price);
//        workout_options[w_id](w_id, w_name, w_price, w_type);
        w_id++;
    }
    MyReadFile.close();


}

int Studio::getNumOfTrainers() const {
    return (int)trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    if (trainers.size() < tid) {
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

int Studio::readNumOfTrainers(const string& line) {
    return stoi(line);
}

void Studio::createNewTrainers(string line) {
    //example input: "6,6,8,4"
    for (int i = 0; i < line.length(); i += 2) {
        trainers[i] = new Trainer((int) (line[i]));
    }
}

void Studio::getWorkoutData(const std::string& line, string *w_name, WorkoutType *w_type, int *w_price) {
    //example line: Yoga, Anaerobic, 90
    unsigned long start_sep = 0;
    unsigned long end_sep = line.find(',');
    *w_name = line.substr(start_sep, end_sep);
    start_sep = end_sep + 2;
    end_sep = line.find(',',start_sep);
    *w_type = convertStringToEnum(line.substr(start_sep, end_sep - start_sep));
    start_sep = end_sep + 1;
    end_sep = line.length();
    *w_price = stoi(line.substr(start_sep,end_sep));
}

WorkoutType Studio::convertStringToEnum(const std::string& string_workout) {
    map <string, WorkoutType> type_map = {
            {"Mixed",     MIXED},
            {"Anaerobic", ANAEROBIC},
            {"Cardio",    CARDIO}
    };
    return type_map[string_workout];
}

std::string Studio::convertEnumToString(WorkoutType enum_workout) {
    map <WorkoutType, string> type_map = {
            {MIXED, "Mixed"},
            {ANAEROBIC, "Anaerobic"},
            {CARDIO, "Cardio"}
    };
    return type_map[enum_workout];
}

bool Studio::extractCommand(const string& user_input, string &command, vector<string> &args) {
    unsigned int length = user_input.size();
    unsigned long start_sep = 0;
    unsigned long end_sep = user_input.find(' ');
    command = user_input.substr(start_sep, end_sep);
    int index = 0;
    start_sep = end_sep + 1;
    end_sep = user_input.find(' ', start_sep);
    while (start_sep != 0){
        string arg = user_input.substr(start_sep, end_sep-start_sep);
        if (raiseOnInvalidArgument(arg)){
            return false;
        }
        args.push_back(arg);
        start_sep = end_sep + 1;
        end_sep = user_input.find(' ', start_sep);
    }
    return true;

}

bool Studio::raiseOnInvalidArgument(string &arg) {
    if (arg.empty()){
        return printInvalidArgumentError();
    }
    // #TODO add more validation checks
    return false;
}

bool Studio::printInvalidArgumentError() {
    cout << "Invalid Arguments, please insert command again" << endl;
    return true;
}

void Studio::createCustomers(vector<string> &args, vector<Customer *> &customerList) {
    // example args: ["Shalom,swt", "Dan,chp", "Alice,mcl", "Bob,fbd"]
    for (auto customerString: args) {
        string name, strategy;
        splitNameStrategy(customerString, name, strategy);
        if (strategy == "swt"){
            customerList.push_back(new SweatyCustomer(name))

        } else if (strategy == "chp"){

        } else if (strategy == "mcl"){

        } else if (strategy == "fbd"){

        }


    }


}
