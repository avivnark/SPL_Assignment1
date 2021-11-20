#include "../include/Studio.h"
#include "../include/Customer.h"


using namespace std;


Customer::Customer(string c_name, int c_id) : name(c_name), id(c_id) {

}

string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

Customer::~Customer() {

}


SweatyCustomer::SweatyCustomer(string name, int id) : Customer(name, id) {

}


std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    unsigned long numOfWorkouts = workout_options.size();
    vector<int> workoutsOrdered;
    for (int i = 0; i < numOfWorkouts; i++)
        if (workout_options.at(i).getType() == CARDIO)
            workoutsOrdered.push_back(i);
    return workoutsOrdered;
}

string SweatyCustomer::toString() const {
    return getName() + ",swt";
}

Customer *SweatyCustomer::clone() {
    return new SweatyCustomer(*this);
}

CheapCustomer::CheapCustomer(string name, int id) : Customer(name, id) {


}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> workoutsOrdered;
    int cheapestWorkoutId;
    int minPrice = workout_options.at(0).getPrice();
    for (int i = 1; i < workout_options.size(); i++) {
        if (workout_options.at(i).getPrice() < minPrice) {
            cheapestWorkoutId = workout_options.at(i).getId();
            minPrice = workout_options.at(i).getPrice();
        }

    }
    workoutsOrdered.push_back(cheapestWorkoutId);
    return workoutsOrdered;
}

string CheapCustomer::toString() const {
    return getName() + ",chp";
}

Customer *CheapCustomer::clone() {
    return new CheapCustomer(*this);
}

HeavyMuscleCustomer::HeavyMuscleCustomer(string name, int id) : Customer(name, id) {

}


std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> workoutsOrdered;
    for (const auto &workout_option: workout_options) {
        if (workout_option.getType() == ANAEROBIC)
            workoutsOrdered.push_back(workout_option.getId());
    }
    std::sort(workoutsOrdered.begin(), workoutsOrdered.end());
    return workoutsOrdered;
}

string HeavyMuscleCustomer::toString() const {
    return getName() + ",mcl";
}

Customer *HeavyMuscleCustomer::clone() {
    return new HeavyMuscleCustomer(*this);
}

FullBodyCustomer::FullBodyCustomer(string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> workoutsOrdered;
    int cheapestCardioId;
    int minPriceCardio;
    bool foundCardio = false;
    int expensiveMixId;
    int maxPriceMix;
    bool foundMix = false;
    int cheapestAnaerobicId;
    int minPriceAnaerobic;
    bool foundAnaerobic = false;
    for (int i = 1; i < workout_options.size(); i++) {
        if (!foundCardio) {
            cheapestCardioId = workout_options.at(i).getId();
            minPriceCardio = workout_options.at(i).getPrice();
            foundCardio = true;
        }
        if (workout_options.at(i).getType() == CARDIO) {
            if (workout_options.at(i).getPrice() < minPriceCardio) {
                cheapestCardioId = workout_options.at(i).getId();
                minPriceCardio = workout_options.at(i).getPrice();
            }
        }
        if (!foundMix) {
            expensiveMixId = workout_options.at(i).getId();
            maxPriceMix = workout_options.at(i).getPrice();
            foundMix = true;
        }
        if (workout_options.at(i).getType() == MIXED) {
            if (workout_options.at(i).getPrice() > maxPriceMix) {
                expensiveMixId = workout_options.at(i).getId();
                maxPriceMix = workout_options.at(i).getPrice();
            }
        }
        if (!foundAnaerobic) {
            cheapestAnaerobicId = workout_options.at(i).getId();
            minPriceAnaerobic = workout_options.at(i).getPrice();
            foundAnaerobic = true;
        }
        if (workout_options.at(i).getType() == MIXED) {
            if (workout_options.at(i).getPrice() < minPriceAnaerobic) {
                cheapestAnaerobicId = workout_options.at(i).getId();
                minPriceAnaerobic = workout_options.at(i).getPrice();
            }
        }

    }
    workoutsOrdered.push_back(cheapestCardioId);
    workoutsOrdered.push_back(expensiveMixId);
    workoutsOrdered.push_back(cheapestAnaerobicId);
    return workoutsOrdered;
}

string FullBodyCustomer::toString() const {
    return getName() + ",fbd";
}

Customer *FullBodyCustomer::clone() {
    return new FullBodyCustomer(*this);
}
