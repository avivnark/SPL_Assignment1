#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Workout.h"
#include "Customer.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    Trainer(const Trainer& other);//Copy
    ~Trainer();//Destructor
    Trainer(Trainer&& other);//Move
    Trainer& operator=(const Trainer & other);//Copy assignment
    Trainer& operator=(Trainer && other);//Move assignment
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();

    unsigned long getNumberOfCustomers();
    void addOrder(OrderPair orderPair);
private:
    int capacity;
    bool open;
    int salary;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif