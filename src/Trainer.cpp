#include "../include/Studio.h"

Trainer::Trainer(int t_capacity): capacity(t_capacity){

}

int Trainer::getCapacity() const {
    return capacity;

}

void Trainer::addCustomer(Customer *customer) {

}

void Trainer::removeCustomer(int id) {

}

Customer *Trainer::getCustomer(int id) {
    for (auto & customer: customersList) {
        if (customer->getId() == id){
            return customer;
        }
    }
    return nullptr;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
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
    return open;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const vector<Workout> &workout_options) {

}