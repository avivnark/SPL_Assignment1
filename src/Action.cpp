
#include "../include/Studio.h"

using namespace std;

BaseAction::BaseAction() {

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    status=ERROR;
    errorMsg = errorMsg;
    std::cout << "Error: " << errorMsg << std::endl;
}

//void BaseAction::logger(string & command, vector<string>& *arguments){
//    string log = command;
//    for (int i = 0; i < (*arguments).size();i++) {
//        log += " " + (*arguments)[i];
//    }
//}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id), customers(customersList){
}

void OpenTrainer::act(Studio &studio) {
    Trainer* t= studio.getTrainer(trainerId);
    if (t == nullptr){
        error("Trainer does not exist");
        return;
    }
    if(t->isOpen()){
        this->error("Trainer is already opened");
        return;
    }
    if (customers.size() > t->getCapacity()){
        error("Not enough spots open for this trainer");
        return;
    }
    t->openTrainer();
    for (auto & customer : customers) {
        t->addCustomer(customer);
    }
}

string OpenTrainer::toString() const {
    string log = "Open" + to_string(trainerId);
    return "delete me";
}

Order::Order(int id): BaseAction(), trainerId(id) {

}

void Order::act(Studio &studio) {
    Trainer* t=studio.getTrainer(trainerId);
    if(t == nullptr || t->isOpen()){
        this->error("Trainer doesn't exist or is not open");
    }
}

std::string Order::toString() const {

}

MoveCustomer::MoveCustomer(int src, int dst, int customerId): BaseAction(),srcTrainer(src),dstTrainer(dst),id(customerId) {

}

void MoveCustomer::act(Studio &studio) {


}

//std::string MoveCustomer::toString() const {
//    return std::string();
//}

Close::Close(int id): BaseAction(), trainerId(id){

}

void Close::act(Studio &studio) {
    Trainer* t=studio.getTrainer(trainerId);
    if(t == nullptr || t->isOpen()){
        this->error("Trainer doesn't exist or is not open");
    }
    int salary = t->getSalary();
    t->closeTrainer();
    std::cout << "Trainer " << trainerId << " closed. Salary " << salary << "NIS" << std::endl;

}

CloseAll::CloseAll() {

}

void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); ++i) {
        Trainer * trainer = studio.getTrainer(i);
        if (trainer->isOpen()){
            // should close the trainer here using the Close act
        }
        // should close studio here
    }
}

//std::string CloseAll::toString() const {
//    return std::string();
//}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {
    for (Workout workout: studio.getWorkoutOptions()) {
        cout << workout.toString() << endl;
    }
}

std::string PrintWorkoutOptions::toString() const {

}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {

}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer * trainer = studio.getTrainer(trainerId);

}


//std::string PrintTrainerStatus::toString() const {
//
//    return std::string();
//}

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Studio &studio) {
    std::vector<BaseAction*> actionLogs = studio.getActionsLog();
    for (auto * actionlog: actionLogs) {
        cout << actionlog->toString() << endl;
    }
}

std::string PrintActionsLog::toString() const {
    return std::string();
}

//BackupStudio::BackupStudio() {
//
//}

//void BackupStudio::act(Studio &studio) {
//
//}

RestoreStudio::RestoreStudio() {

}

//std::string RestoreStudio::toString() const {
//    return std::string();
//}
