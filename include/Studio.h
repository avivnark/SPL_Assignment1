#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Trainer.h"
#include "Workout.h"
#include "Action.h"


class Studio{
public:
	Studio();
    Studio(const Studio& other);//Copy
    ~Studio();//Destructor
    Studio(Studio && other);//Move
    Studio& operator=(const Studio & other);//Copy assignment
    Studio& operator=(Studio && other);//Move assignment
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    void clearStudioResources();

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    int sequentialCustomerId;

    int readNumOfTrainers(const std::string& line);
    void createCustomers(std::vector<string> & args, std::vector<Customer*> & customerList);
    void createNewTrainers(std::string line);
    void getWorkoutData(const std::string& line,string* w_name,WorkoutType* w_type,int* w_price);
    WorkoutType convertStringToEnum(const std::string& string_workout);
    std::string convertEnumToString(WorkoutType enum_workout);
    bool extractCommand(const string& user_input, string & command, std::vector<string> & args);
    bool raiseOnInvalidArgument(string & arg);
    bool printInvalidArgumentError();
    void splitNameStrategy(string & customerString, string & name, string & strategy);
};

#endif