#include "../include/Studio.h"
#include <iostream>
#include <fstream>
#include "map"
#include "string"

using namespace std;

void Studio::start() {
    std::cout << "Studio is now Open!" << std::endl;

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

int Studio::readNumOfTrainers(string line) {
    return stoi(line);
}

void Studio::createNewTrainers(string line) {
    //example input: "6,6,8,4"
    for (int i = 0; i < line.length(); i += 2) {
        trainers[i] = new Trainer((int) (line[i]));
    }
}

void Studio::getWorkoutData(std::string line, string *w_name, WorkoutType *w_type, int *w_price) {
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

WorkoutType Studio::convertStringToEnum(std::string string_workout) {
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
