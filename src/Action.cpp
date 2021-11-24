
#include "../include/Studio.h"
#include "../include/Action.h"

extern Studio *backup;

using namespace std;

BaseAction::BaseAction() = default;

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    this->errorMsg = "Error: " + errorMsg;
    std::cout << this->errorMsg << std::endl;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

BaseAction::BaseAction(const BaseAction &other) {

}

BaseAction::~BaseAction() = default;

BaseAction &BaseAction::operator=(BaseAction &&other) {
    return *this;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id),
                                                                           customers(std::move(customersList)) {
}

OpenTrainer::~OpenTrainer() {
    for (auto *customer: customers) {
        delete customer;
    }
    customers.clear();
}


BaseAction &OpenTrainer::operator=(BaseAction &&other) {
    customers = std::move(dynamic_cast<OpenTrainer &&>(other).customers);
    return *this;
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
    if ((int) customers.size() > t->getCapacity()) {
        error("Not enough spots open for this trainer");
        return;
    }
    t->openTrainer();
    for (auto *customer: customers) {
        t->addCustomer(customer->clone());
    }
    complete();
}

string OpenTrainer::toString() const {
    string log = "open " + to_string(trainerId);
    for (auto *customer: customers) {
        log += " " + customer->toString();
    }
    if (getStatus() == COMPLETED) {
        log += " Completed";
    } else {
        log += " " + getErrorMsg();
    }
    return log;
}

BaseAction *OpenTrainer::clone() {
    return new OpenTrainer(*this);
}

OpenTrainer::OpenTrainer(const OpenTrainer &other) : trainerId(other.trainerId) {
    customers.reserve(other.customers.size());
    for (auto *otherCustomer: other.customers) {
        customers.push_back(otherCustomer->clone());
    }
}

Order::Order(int id) : BaseAction(), trainerId(id) {

}

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer->isOpen()) {
        this->error("Trainer does not exist or is not open");
        return;
    }
    for (auto *customer: trainer->getCustomers()) {
        std::vector<int> customerWorkoutOrders = customer->order(studio.getWorkoutOptions());
        trainer->order(customer->getId(), customerWorkoutOrders, studio.getWorkoutOptions());
    }
    complete();
}

std::string Order::toString() const {
    string log = "order " + to_string(trainerId);
    if (getStatus() == COMPLETED) {
        log += " Completed";
    } else {
        log += " " + getErrorMsg();
    }
    return log;

}

BaseAction *Order::clone() {
    return new Order(*this);
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId)
        : BaseAction(), srcTrainer(src), dstTrainer(dst), id(customerId) {

}

void MoveCustomer::act(Studio &studio) {
    Trainer *src = studio.getTrainer(srcTrainer);
    Trainer *dst = studio.getTrainer(dstTrainer);
    if (src == nullptr || dst == nullptr) {
        error("Cannot move customer");
        return;
    }
    if (src->getCustomer(id) == nullptr) {
        error("Cannot move customer");
        return;
    }
    if ((int) dst->getCustomers().size() + 1 > dst->getCapacity()) {
        error("Cannot move customer");
        return;
    }
    if (!dst->isOpen() || !src->isOpen()) {
        error("Cannot move customer");
        return;
    }
    // move customer from source trainer to destination trainer
    dst->addCustomer(src->getCustomer(id)->clone());
    for (auto orderPair: src->getOrders()) {
        if (orderPair.first == id) {
            dst->addOrder(orderPair);
        }
    }
    src->removeCustomer(id);
    if (src->getNumberOfCustomers() ==
        0) { // move trainer deletes customers, when restoring, under copy assignment operator, i
        auto *closeTrainer = new Close(srcTrainer);
        closeTrainer->act(studio);
        delete closeTrainer;
    }
    complete();
}

std::string MoveCustomer::toString() const {
    string log = "move " + to_string(srcTrainer) + " " + to_string(dstTrainer) + " " + to_string(id);
    if (getStatus() == COMPLETED) {
        log += " Completed";
    } else {
        log += " " + getErrorMsg();
    }
    return log;

}

BaseAction *MoveCustomer::clone() {
    return new MoveCustomer(*this);
}

Close::Close(int id) : BaseAction(), trainerId(id) {

}

void Close::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if (t == nullptr || !t->isOpen()) {
        this->error("Trainer does not exist or is not open");
        return;
    }
    int salary = t->getSalary();
    t->closeTrainer();
    std::cout << "Trainer " << trainerId << " closed. Salary " << salary << "NIS" << std::endl;
    complete();
}

std::string Close::toString() const {
    string log = "close " + to_string(trainerId);
    if (getStatus() == COMPLETED) {
        log += " Completed";
    } else {
        log += " " + getErrorMsg();
    }
    return log;
}

BaseAction *Close::clone() {
    return new Close(*this);
}

CloseAll::CloseAll() {

}

void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); ++i) {
        Trainer *trainer = studio.getTrainer(i);
        if (trainer->isOpen()) {
            Close *closeTrainer = new Close(i);
            closeTrainer->act(studio);
            delete closeTrainer;
        }
        complete();
    }
}

std::string CloseAll::toString() const {
    return "closeall Completed";
}

BaseAction *CloseAll::clone() {
    return new CloseAll(*this);
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
    return "workout_options Completed";

}

BaseAction *PrintWorkoutOptions::clone() {
    return new PrintWorkoutOptions(*this);
}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {

}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    string status = "Trainer " + to_string(trainerId) + " status: ";
    bool isOpen = trainer->isOpen();
    if (isOpen) {
        status += "open\nCustomers:\n";
        for (auto *customer: trainer->getCustomers()) {
            status += to_string(customer->getId()) + " " + customer->getName() + "\n";
        }
        status += "Orders:\n";
        for (OrderPair pair: trainer->getOrders()) { // pair -> (customer_id, workout)
            status += pair.second.getName() + " " + to_string(pair.second.getPrice()) + "NIS " + to_string(pair.first) +
                      "\n";
        }
        status += "Current Trainer's Salary: " + to_string(trainer->getSalary()) + "NIS";
    } else {
        status += "closed";
    }
    cout << status << endl;
    complete();
}


std::string PrintTrainerStatus::toString() const {
    string log = "status " + to_string(trainerId);
    if (getStatus() == COMPLETED) {
        log += " Completed";
    } else {
        log += " " + getErrorMsg();
    }
    return log;
}

BaseAction *PrintTrainerStatus::clone() {
    return new PrintTrainerStatus(*this);
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

BaseAction *PrintActionsLog::clone() {
    return new PrintActionsLog(*this);
}

BackupStudio::BackupStudio() : BaseAction() {

}

void BackupStudio::act(Studio &studio) {
    delete backup;
    backup = new Studio(studio);
    complete();
}

std::string BackupStudio::toString() const {
    return "backup Completed";
}

BaseAction *BackupStudio::clone() {
    return new BackupStudio(*this);
}

RestoreStudio::RestoreStudio() : BaseAction() {

}

void RestoreStudio::act(Studio &studio) {
    if (backup == nullptr) {
        error("No backup available");
        return;
    }
    studio = *backup; //copy assignment called
    complete();
}

std::string RestoreStudio::toString() const {
    string log = "restore ";
    if (getStatus() == COMPLETED) {
        log += "Completed";
    } else {
        log += getErrorMsg();
    }
    return log;
}

BaseAction *RestoreStudio::clone() {
    return new RestoreStudio(*this);
}
