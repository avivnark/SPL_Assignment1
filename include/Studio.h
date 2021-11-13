#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"


class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;

    int readNumOfTrainers(std::string line);
    void createNewTrainers(std::string line);
    void getWorkoutData(std::string line,string* w_name,WorkoutType* w_type,int* w_price);
    WorkoutType convertStringToEnum(std::string string_workout);
    std::string convertEnumToString(WorkoutType enum_workout);

};

#endif