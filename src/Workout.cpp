#include "../include/Studio.h"
#include "map"

using namespace std;

Workout::Workout(int w_id, string w_name, int w_price, WorkoutType w_type):id(w_id),name(w_name),price(w_price), type(w_type) {

}

int Workout::getId() const {
    return id;
}

std::string Workout::getName() const {
    return name;
}

int Workout::getPrice() const {
    return price;
}

WorkoutType Workout::getType() const {
    return type;
}

string Workout::toString() const {
    map <WorkoutType, string> type_map = {
            {MIXED, "Mixed"},
            {ANAEROBIC, "Anaerobic"},
            {CARDIO, "Cardio"}
    };
    return name + ", " + type_map[type] + ", " + to_string(price);
}

