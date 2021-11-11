#include "../include/Action.h"
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

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id){
    customers(&customersList);

}

string OpenTrainer::toString() const {
    string log = "Open" << trainerId <<
    return
}

void OpenTrainer::act(Studio &studio) {
    Trainer* t=studio.getTrainer(trainerId);
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

void Order::act(Studio &studio) {
    Trainer* t=studio.getTrainer(trainerId);
    if(t == nullptr || t->isOpen()){
        this->error("Trainer doesn't exist or is not open");
    }
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) {

}

void MoveCustomer::act(Studio &studio) {

}

std::string MoveCustomer::toString() const {
    return std::string();
}

Close::Close(int id) {
    this->act()
}

void Close::act(Studio &studio) {
    Trainer* t=studio.getTrainer(trainerId);
    if(t == nullptr || t->isOpen()){
        this->error("Trainer doesn't exist or is not open");
    }
    int salary = t->getSalary();
    t->closeTrainer();
    std::cout << "Trainer " << id << " closed. Salary " << salary << "NIS" << std::endl;

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

std::string CloseAll::toString() const {
    return std::string();
}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {
    for (Workout * workout: studio.getWorkoutOptions()) {
        cout << workout->toString() << endl;
    }

}

void PrintTrainerStatus::act(Studio &studio) {

}

std::string PrintTrainerStatus::toString() const {

    return std::string();
}

PrintActionsLog::PrintActionsLog() {

}

std::string PrintActionsLog::toString() const {
    return std::string();
}

BackupStudio::BackupStudio() {

}

void BackupStudio::act(Studio &studio) {

}

RestoreStudio::RestoreStudio() {

}

std::string RestoreStudio::toString() const {
    return std::string();
}
