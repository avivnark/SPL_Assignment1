#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Workout.h"
#include "Customer.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    /*
     * right now destroying trainer deletes it's customer list.
     * should reconsider.
     * Are the customers are his to delete?
     * Is it efficient or necessary to clone customers into a trainer or is it enough to point the studio's customers?
     */

    Trainer(int t_capacity);
    Trainer(const Trainer& other);
    ~Trainer();
    Trainer(Trainer&& other);
    Trainer& operator=(const Trainer & other);
    Trainer& operator=(Trainer && other);
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
private:
    int capacity;
    bool open;
    int salary;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif