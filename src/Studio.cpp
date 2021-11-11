#include "../include/Studio.h"
#include <iostream>
#include <ifstream>
#include "algorithm"
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
    int numOfTrainers;
    ifstream MyReadFile(configFilePath);
    getline (MyReadFile, line);
    numOfTrainers = int(line);
    trainers.reserve(numOfTrainers)
    getline (MyReadFile, line);
    for(i=0;i<numOfTrainers;i++){
        trainers[i] = new *Trainer(int(line.substr(i, i + 1)));
        line=line.substr(i+2,line.length());
    }
    int index=0;
    while (getline (MyReadFile, line)) {
        int comma = line.find(",");
        string name=line.substr(0,comma+1);
        line=line.substr(comma+1,line.length());
        string w_type=line.substr(0,comma+1);
        toUpperCase(&w_type);
        line=line.substr(comma+1,line.length());
        int price=(int)line;
        map<string, WorkoutType> type_map = boost::map_list_of("MIXED", MIXED)("ANAEROBIC", ANAEROBIC)("CARDIO",CARDIO);
        workout_options[index]=new Workout(index,name,price,type_map[w_type]);
        index++;
    }
    MyReadFile.close();


}

Studio:: void toUpperCase(string & w_type){
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}

int Studio::getNumOfTrainers() const {
    return int(trainers.size())
}

Trainer *Studio::getTrainer(int tid) {
    if (trainers.size()<tid){
        return nullptr;

    }
    return &trainers[tid];
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}
