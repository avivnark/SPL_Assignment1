#include "../include/Studio.h"
#include "../include/Customer.h"
#include "algorithm"


using namespace std;


Customer::Customer(string c_name, int c_id) : name(c_name), id(c_id) {

}

string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

Customer::~Customer() = default;


SweatyCustomer::SweatyCustomer(string name, int id) : Customer(name, id) {

}


std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    int numOfWorkouts = (int) workout_options.size();
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
    for (int i = 1; i < (int) workout_options.size(); i++) {
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
    std::sort(workoutsOrdered.begin(), workoutsOrdered.end(),
              [&workout_options](int id1, int id2) -> bool {
                  return workout_options.at(id1).getPrice() -
                         workout_options.at(id2).getPrice();
              });
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
    int cheapestCardioId, minPriceCardio;
    int cheapestAnaerobicId, minPriceAnaerobic;
    int expensiveMixId, maxPriceMix;
    bool foundCardio, foundMix, foundAnaerobic;
    foundCardio = foundMix = foundAnaerobic = false;
    for (const auto &workout_option: workout_options) {
        if (workout_option.getType() == CARDIO) {
            if (!foundCardio) {
                cheapestCardioId = workout_option.getId();
                minPriceCardio = workout_option.getPrice();
                foundCardio = true;
            } else if (workout_option.getPrice() < minPriceCardio) {
                cheapestCardioId = workout_option.getId();
                minPriceCardio = workout_option.getPrice();
            }
        }
        if (workout_option.getType() == MIXED) {
            if (!foundMix) {
                expensiveMixId = workout_option.getId();
                maxPriceMix = workout_option.getPrice();
                foundMix = true;
            } else if (workout_option.getPrice() > maxPriceMix) {
                expensiveMixId = workout_option.getId();
                maxPriceMix = workout_option.getPrice();
            }
        }
        if (workout_option.getType() == ANAEROBIC) {
            if (!foundAnaerobic) {
                cheapestAnaerobicId = workout_option.getId();
                minPriceAnaerobic = workout_option.getPrice();
                foundAnaerobic = true;
            } else if (workout_option.getPrice() < minPriceAnaerobic) {
                cheapestAnaerobicId = workout_option.getId();
                minPriceAnaerobic = workout_option.getPrice();
            }
        }
    }
    if (foundCardio) {
        workoutsOrdered.push_back(cheapestCardioId);
    }
    if (foundMix) {
        workoutsOrdered.push_back(expensiveMixId);
    }
    if (foundAnaerobic) {
        workoutsOrdered.push_back(cheapestAnaerobicId);
    }
    return workoutsOrdered;
}

string FullBodyCustomer::toString() const {
    return getName() + ",fbd";
}

Customer *FullBodyCustomer::clone() {
    return new FullBodyCustomer(*this);
}
