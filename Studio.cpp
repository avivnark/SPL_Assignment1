#include <iostream>
#include <ifstream>
#include "Studio.h"
#include "string"

using namespace std;

void Studio::start() {
    std::cout << "Hello, World!" << std::endl;
}

Studio::Studio() {

}

Studio::Studio(const string &configFilePath) {
    string line;
    int numOfTrainers;
    ifstream MyReadFile(configFilePath);
    int index = 0;
    getline (MyReadFile, line);
    numOfTrainers = int(line);
    trainers.reserve(numOfTrainers)
    getline (MyReadFile, line);
    for(i=0;i<numOfTrainers;i++){
        trainers[i](int(line.substr(i, i + 1)));
        line=line.substr(i+2,line.length());
    }
    index=0;
    while (getline (MyReadFile, line)) {
        int comma = line.find(",");
        string name=line.substr(0,comma+1);
        line=line.substr(comma+1,line.length());
        string type=line.substr(0,comma+1);
        line=line.substr(comma+1,line.length());
        int price=(int)line;
        workout_options[index](index,name,type,price);
        index++;
    }
    MyReadFile.close();


}

int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    return &trainers[tid];
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}
