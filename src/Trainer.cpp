
#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity) {

}

int Trainer::getCapacity() const {
    return 0git;
}

void Trainer::addCustomer(Customer *customer) {

}

void Trainer::removeCustomer(int id) {

}

Customer *Trainer::getCustomer(int id) {
    return nullptr;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return <#initializer#>;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return <#initializer#>;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {

}

void Trainer::openTrainer() {
    open = true;
}

void Trainer::closeTrainer() {
    open = false;
}

int Trainer::getSalary() {
    return 0;
}

bool Trainer::isOpen() {
    return false;
}


