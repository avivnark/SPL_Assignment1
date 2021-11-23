#include "../include/Studio.h"
#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity) : capacity(t_capacity) {
    salary = 0;
    open = false;
}

Trainer::Trainer(const Trainer &other) : capacity(other.capacity), salary(other.salary), open(other.open) {
    customersList.reserve(other.customersList.size());
    for (auto *customer: other.customersList) {
        customersList.push_back(customer->clone());
    }
    orderList.reserve(other.orderList.size());
    for (auto pair: other.orderList) {
        orderList.push_back(pair);
    }
}

Trainer::Trainer(Trainer &&other) : capacity(other.capacity), salary(other.salary), open(other.open) {
    for (auto *customer: customersList) { // could possibly cause concurrent issues, should think about it
        delete customer;
        customer = nullptr;
    }
    customersList.clear();
    for (auto pair: orderList) { // could possibly cause concurrent issues, should think about it
        delete &pair;
        //pair = nullptr;
    }
    orderList.clear();
    customersList.reserve(other.customersList.size());
    for (auto *customer: other.customersList) {
        customersList.push_back(customer);
    }
    orderList.reserve(other.orderList.size());
    for (auto pair: other.orderList) {
        orderList.push_back(pair);
    }
}

Trainer::~Trainer() {
    for (auto *customer: customersList) {
        delete customer;
    }
    customersList.clear();
    orderList.clear();
}

Trainer &Trainer::operator=(const Trainer &other) {
    return *this;

}

Trainer &Trainer::operator=(Trainer &&other) {
    customersList = std::move(other.customersList);
    return *this;
}

int Trainer::getCapacity() const {
    return capacity;

}

void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer->clone());
}

void Trainer::removeCustomer(int id) {
    int position = 0;
    for (auto *customer: customersList) {
        if (customer->getId() == id) {
            delete customer;
            break;
        }
        position++;
    }
    customersList.erase(customersList.begin() + position);
    vector<OrderPair > updatedOrderList;
    for (auto orderPair: orderList) {
        if (orderPair.first != id){
            updatedOrderList.push_back(orderPair);
        }
    }
    orderList = std::move(updatedOrderList);

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

void Trainer::closeTrainer() {
    for (auto *customer: customersList) {
        delete customer;
    }
    customersList.clear();
    orderList.clear();
    salary += getSalary();
    open = false;
}

int Trainer::getSalary() {
    int currentSalary = 0;
    for (auto orderPair: orderList) {
        currentSalary += orderPair.second.getPrice();
    }
    return salary + currentSalary;
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
        Customer * customer = getCustomer(customer_id);
        cout << customer->getName() + " Is Doing " + workout_options[w_id].getName() + "\n";
    }
}

unsigned long Trainer::getNumberOfCustomers() {
    return customersList.size();
}

void Trainer::addOrder(OrderPair orderPair) {
    orderList.push_back(orderPair);
}

