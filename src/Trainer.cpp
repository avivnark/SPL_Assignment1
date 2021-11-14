#include "../include/Studio.h"

Trainer::Trainer(int t_capacity) : capacity(t_capacity) {

}

int Trainer::getCapacity() const {
    return capacity;

}

void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
    orderList.push_back(customer->getId(), customer.)
}

void Trainer::removeCustomer(int id) {
    int counter = 0;
    while(counter<customersList.size()){
        if(id == customersList[counter]->getId()){
            delete customersList[counter];
            erase(customersList,counter);
            break;
        }
        counter++;
    }
    customersList[counter]->~Customer();
}

Customer *Trainer::getCustomer(int id) {
    for (auto &customer: customersList) {
        if (customer->getId() == id) {
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

void Trainer::closeTrainer() {//lo laasot
    open = false;
    for (auto *customer: customersList) { // could possibly cause concurrent issues, should think about it
        removeCustomer(customer->getId());
    }
    customersList.clear();
}

int Trainer::getSalary() {
    int totalSalary = 0;
    for(OrderPair orderPair: orderList){
        totalSalary += orderPair.second.getPrice();
    }
    return totalSalary;
}

bool Trainer::isOpen() {
    return open;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const vector<Workout> &workout_options) {
//    typedef std::pair<int, Workout> OrderPair;
//    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    for (int w_id: workout_ids) {
        OrderPair orderPair(customer_id, workout_options[w_id]);
        orderList.push_back(orderPair);
    }
}