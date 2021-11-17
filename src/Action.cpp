
#include "../include/Studio.h"
extern Studio * backup;

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
    status = ERROR;
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

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {
}

void OpenTrainer::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if (t == nullptr) {
        error("Trainer does not exist");
        return;
    }
    if (t->isOpen()) {
        this->error("Trainer is already opened");
        return;
    }
    if (customers.size() > t->getCapacity()) {
        error("Not enough spots open for this trainer");
        return;
    }
    t->openTrainer();
    for (auto &customer: customers) {
        t->addCustomer(customer);
    }
    complete();
}

string OpenTrainer::toString() const {
    string log = "open " + to_string(trainerId) + " ";
    for (auto *customer: customers) {
        log += customer->toString() + " ";
    }
    if (getStatus() == COMPLETED) {
        log += "Completed";
    } else {
        log += "Error: " + getErrorMsg();
    }
    return log;
}

Order::Order(int id) : BaseAction(), trainerId(id) {

}

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer->isOpen()) {
        this->error("Trainer doesn't exist or is not open");
    }
    for (auto * customer: trainer->getCustomers()) {
        std::vector<int> customerWorkoutOrders = customer->order(studio.getWorkoutOptions());
        trainer->order(customer->getId(), customerWorkoutOrders, studio.getWorkoutOptions());
    }
    complete();
}

std::string Order::toString() const {
    string log = "order " + to_string(trainerId);
    if (getStatus() == COMPLETED) {
        log += "Completed";
    } else {
        log += "Error: " + getErrorMsg();
    }
    return log;

}

MoveCustomer::MoveCustomer(int src, int dst, int customerId)
        : BaseAction(), srcTrainer(src), dstTrainer(dst), id(customerId) {

}

void MoveCustomer::act(Studio &studio) {
    Trainer* src=studio.getTrainer(srcTrainer);
    Trainer* dst=studio.getTrainer(dstTrainer);
    if (dst->getCustomers().size() + 1 > dst->getCapacity()){
        error("Exceeding capacity");
        return;
    }
    if (!dst->isOpen()){
        error("Trainer is not open");
        return;
    }
    dst->addCustomer(src->getCustomer(id));
    src->removeCustomer(id);
}

std::string MoveCustomer::toString() const {
    return "move " + to_string(srcTrainer) + " " + to_string(dstTrainer) + " " + to_string(id);
}

Close::Close(int id) : BaseAction(), trainerId(id) {

}

void Close::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if (t == nullptr || !t->isOpen()) {
        this->error("Trainer doesn't exist or is not open");
        return;
    }
    int salary = t->getSalary();
    t->closeTrainer();
    std::cout << "Trainer " << trainerId << " closed. Salary " << salary << "NIS" << std::endl;
    complete();

}

std::string Close::toString() const {
    return "close " + to_string(trainerId);
}

CloseAll::CloseAll() {

}

void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); ++i) {
        Trainer *trainer = studio.getTrainer(i);
        if (trainer->isOpen()) {
            Close * closeTrainer = new Close(i);
            closeTrainer->act(studio);
        }
        complete();
    }
}

std::string CloseAll::toString() const {
    return "closeall Completed";
}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {
    for (Workout workout: studio.getWorkoutOptions()) {
        cout << workout.toString() << endl;
    }
    complete();
}

std::string PrintWorkoutOptions::toString() const {
    return "workout_options";

}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {

}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    string status = "Trainer " + to_string(trainerId) + " status: ";
    bool isOpen = trainer->isOpen();
    if (isOpen){
        status += "open\nCustomers:\n";
        for (auto * customer: trainer->getCustomers()) {
            status += to_string(customer->getId()) + " " + customer->getName() + "\n";
        }
        status += "Orders:\n";
        for (OrderPair pair: trainer->getOrders()) { // pair -> (customer_id, workout)
            status += pair.second.getName() + " " + to_string(pair.second.getPrice()) + "NIS " + to_string(pair.first) + "\n";
        }
        status += "Current Trainer's Salary: " + to_string(trainer->getSalary()) + "NIS";
    } else{
        status += "closed";
    }
    cout << status << endl;
    complete();
}


std::string PrintTrainerStatus::toString() const {
    string log = "status " + to_string(trainerId);
    if (getStatus() == COMPLETED) {
        log += "Completed";
    } else {
        log += "Error: " + getErrorMsg();
    }
    return log;
}

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Studio &studio) {
    std::vector<BaseAction *> actionLogs = studio.getActionsLog();
    for (auto *actionLog: actionLogs) {
        cout << actionLog->toString() << endl;
    }
    complete();
}

std::string PrintActionsLog::toString() const {
    return "log";
}

BackupStudio::BackupStudio():BaseAction(){

}

void BackupStudio::act(Studio &studio) {
    backup = new Studio(studio);
}

std::string BackupStudio::toString() const {
    return "backup";
}

RestoreStudio::RestoreStudio():BaseAction() {

}

void RestoreStudio::act(Studio &studio) {
    if (backup == nullptr){
        error("No backup available");
        return;
    }
    backup = new Studio(studio);
    complete();
}

std::string RestoreStudio::toString() const {
    string log = "restore ";
    if (getStatus() == COMPLETED) {
        log += "Completed";
    } else {
        log += "Error: " + getErrorMsg();
    }
    return log;
}
