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

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id){
    customers(&customersList);

}

std::string OpenTrainer::toString() const {
    return std::string();
}

void OpenTrainer::act(Studio &studio) {
    Trainer* t=studio.getTrainer(trainerId);
    if(t != nullptr && t->isOpen()){
        this->error("Trainer is already opened");
    }
    if(!t->isOpen()) {
        t->openTrainer();
    }
}

void Order::act(Studio &studio) {

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

}

std::string CloseAll::toString() const {
    return std::string();
}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {

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
