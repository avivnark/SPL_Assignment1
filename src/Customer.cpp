#include "../include/Studio.h"

using namespace std;


Customer::Customer(string c_name, int c_id):name(c_name),id(c_id) {

}

string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}


SweatyCustomer::SweatyCustomer(string name, int id) : Customer(name, id) {

}

vector<int> SweatyCustomer::order(const ::vector <Workout> &workout_options) {
    return {1,2,3};
}

string SweatyCustomer::toString() const {
    return "swt";
}

CheapCustomer::CheapCustomer(string name, int id) : Customer(name, id) {


}

vector<int> CheapCustomer::order(const vector <Workout> &workout_options) {
    return {1,2,3};
}

string CheapCustomer::toString() const {
    return "chp";
}

HeavyMuscleCustomer::HeavyMuscleCustomer(string name, int id) : Customer(name, id) {

}

vector<int> HeavyMuscleCustomer::order(const vector <Workout> &workout_options) {
    return {1,2,3};
}

string HeavyMuscleCustomer::toString() const {
    return "mcl";
}

FullBodyCustomer::FullBodyCustomer(string name, int id) : Customer(name, id) {

}

vector<int> FullBodyCustomer::order(const vector <Workout> &workout_options) {
    return {1,2,3};
}

string FullBodyCustomer::toString() const {
    return "fbd";
}
