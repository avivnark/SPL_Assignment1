#include "../include/Studio.h"
#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity) : capacity(t_capacity), open(false), salary(0) {
}

Trainer::Trainer(const Trainer &other) : capacity(other.capacity), open(other.open), salary(other.salary),
                                         orderList(other.orderList) { // copy constructor
    customersList.reserve(other.customersList.size());
    for (auto *customer: other.customersList) {
        customersList.push_back(customer->clone());
    }
}

Trainer::Trainer(Trainer &&other) : capacity(other.capacity), open(other.open),
                                    salary(other.salary) { // move constructor
    clearTrainerResources();

    customersList.reserve(other.customersList.size());
    for (auto *customer: other.customersList) {
        customersList.push_back(customer);
    }
    other.customersList.clear();
}

Trainer::~Trainer() { // destructor
    clearTrainerResources();
}

Trainer &Trainer::operator=(const Trainer &other) { // copy assignment operator
    clearTrainerResources();

    customersList.reserve(other.customersList.size());
    for (auto *customer: other.customersList) {
        customersList.push_back(customer->clone());
    }
    for (const auto& orderPair: other.orderList) {
        orderList.push_back(orderPair);
    }
    return *this;
}

Trainer &Trainer::operator=(Trainer &&other) { // move assignment operator
    clearTrainerResources();

    customersList.reserve(other.customersList.size());
    for (auto *otherCustomer: other.customersList) {
        customersList.push_back(otherCustomer);
    }
    for (auto orderPair: other.orderList) {
        orderList.push_back(std::move(orderPair));
    }
    other.customersList.clear();
    return *this;
}

int Trainer::getCapacity() const {
    return capacity;

}

void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
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
    vector<OrderPair> updatedOrderList;
    for (auto orderPair: orderList) {
        if (orderPair.first != id) {
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
    salary += getCurrentSalary();
    open = false;
    clearTrainerResources();
}

int Trainer::getSalary() {
    return salary + getCurrentSalary();
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
        Customer *customer = getCustomer(customer_id);
        cout << customer->getName() + " Is Doing " + workout_options[w_id].getName() + "\n";
    }
}

unsigned long Trainer::getNumberOfCustomers() {
    return customersList.size();
}

void Trainer::addOrder(const OrderPair& orderPair) {
    orderList.push_back(orderPair);
}

void Trainer::clearTrainerResources() {
    for (auto *customer: customersList) {
        delete customer;
    }
    customersList.clear();
    orderList.clear();
}

int Trainer::getCurrentSalary() {
    int currentSalary = 0;
    for (auto orderPair: orderList) {
        currentSalary += orderPair.second.getPrice();
    }
    return currentSalary;
}

