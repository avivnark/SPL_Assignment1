#ifndef WORKOUT_H_
#define WORKOUT_H_

#include <string>

using namespace std;

enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO
};

class Workout{
public:
    Workout(int w_id,string w_name, int w_price, WorkoutType w_type);
//    Workout& operator=(const Workout & other);
    int getId() const;
    string getName() const;
    int getPrice() const;
    WorkoutType getType() const;
    string toString() const; //added
private:
	const int id;
    const string name;
    const int price;
    const WorkoutType type;
};

#endif