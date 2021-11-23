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
        if (workout_options.at(i).getPrice() < minPrice){
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
    vector<Workout> workoutsOrdered;
    vector<int> output;
    for (const auto & workout_option : workout_options) {
        if (workout_option.getType() == ANAEROBIC)
            workoutsOrdered.push_back(workout_option);
    }
    int i, j;
    for (int i = 1; i < workoutsOrdered.size(); i++)
    {
        Workout key = workoutsOrdered[i];
        j = i - 1;
        while (j >= 0 && workoutsOrdered[j].getPrice() < key.getPrice())
        {
            workoutsOrdered[j + 1] = workoutsOrdered[j];
            j--;
        }
        workoutsOrdered[j + 1] = key;
    }
    for (int s=workoutsOrdered.size()-1; s>=0; s--) {
        output.push_back(workoutsOrdered.at(s).getId());
    }
    return output;
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
    for (int i = 0; i < workout_options.size(); i++) {
        if (workout_options.at(i).getType() == CARDIO) {
            if (!foundCardio) {
                cheapestCardioId = workout_options.at(i).getId();
                minPriceCardio = workout_options.at(i).getPrice();
                foundCardio = true;
            }
            else if (workout_options.at(i).getPrice() < minPriceCardio) {
                cheapestCardioId = workout_options.at(i).getId();
                minPriceCardio = workout_options.at(i).getPrice();
            }
        }
        if (workout_options.at(i).getType() == MIXED) {
            if (!foundMix) {
                expensiveMixId = workout_options.at(i).getId();
                maxPriceMix = workout_options.at(i).getPrice();
                foundMix = true;
            }
            else if (workout_options.at(i).getPrice() > maxPriceMix) {
                expensiveMixId = workout_options.at(i).getId();
                maxPriceMix = workout_options.at(i).getPrice();
            }
        }
        if (workout_options.at(i).getType() == ANAEROBIC) {
            if (!foundAnaerobic) {
                cheapestAnaerobicId = workout_options.at(i).getId();
                minPriceAnaerobic = workout_options.at(i).getPrice();
                foundAnaerobic = true;
            }
            else if (workout_options.at(i).getPrice() < minPriceAnaerobic) {
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
