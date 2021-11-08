#include "Customer.h"


Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id) {

}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}


SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SweatyCustomer::order(const std::vector <Workout> &workout_options) {
    return nullptr;
}

std::string SweatyCustomer::toString() const {
    return "swt";
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {


}y

std::vector<int> CheapCustomer::order(const std::vector <Workout> &workout_options) {
    return nullptr;
}

std::string CheapCustomer::toString() const {
    return "chp";
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> HeavyMuscleCustomer::order(const std::vector <Workout> &workout_options) {
    return nullptr;
}

std::string HeavyMuscleCustomer::toString() const {
    return "mcl";
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector <Workout> &workout_options) {
    return nullptr;
}

std::string FullBodyCustomer::toString() const {
    return "fbd";
}



