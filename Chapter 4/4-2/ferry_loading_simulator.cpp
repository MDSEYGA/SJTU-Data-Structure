#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

template <class elemType>
class queue {
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() {}
};

template <class elemType>
class linkQueue: public queue<elemType> {
private:
    struct node {
        elemType data;
        node* next;
        node(const elemType &x, node* N = nullptr) {
            data = x;
            next = N;
        }
        node(): next(nullptr) {}
        ~node() {}
    };

    node* front;
    node* rear;

public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() const;
};


template <class elemType>
linkQueue<elemType>::linkQueue() {
    front = rear = nullptr;
}

template <class elemType>
linkQueue<elemType>::~linkQueue() {
    node* tmp;
    while (front != nullptr) {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template <class elemType>
bool linkQueue<elemType>::isEmpty() const {
    return front == nullptr;
}

template <class elemType>
elemType linkQueue<elemType>::getHead() const {
    return front->data;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
    if (rear == nullptr) {
        front = rear = new node(x);
    } else {
        rear->next = new node(x);
        rear = rear->next;
    }
}

template <class elemType>
elemType linkQueue<elemType>::deQueue() {
    node* tmp = front;
    elemType value = front->data;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete tmp;
    return value;
}

/**
 * This simulation models the arrival and boarding of cars and trucks at a ferry terminal.
 * Vehicles arrive randomly based on provided probabilities and are placed in separate queues.
 * Every `ferry_interval` minutes, a ferry arrives and begins loading vehicles.
 * Waiting time is tracked for each vehicle and averaged at the end of the simulation.
 *
 * @param simulation_time     Total time (in minutes) to run the simulation.
 * @param prob_car            Probability (0 to 1) of a car arriving in a given minute.
 * @param prob_truck          Probability (0 to 1) of a truck arriving in a given minute.
 * @param ferry_interval      Time interval (in minutes) between ferry arrivals. Default is 10.
 * @param ferry_capacity      Maximum number of vehicles a ferry can carry. Default is 10.
 */
void simulate_ferry_loading(
    const int simulation_time,
    const double prob_car,
    const double prob_truck,
    const int ferry_interval = 10,
    const int ferry_capacity = 10
) {
    linkQueue<int> car_queue;
    linkQueue<int> truck_queue;

    int current_time = 0;
    int car_count = 0, truck_count = 0;
    int car_time = 0, truck_time = 0;
    
    while (current_time < simulation_time) {
        // Generate cars and trucks
        if ((double)rand() / RAND_MAX < prob_car) {
            car_queue.enQueue(current_time);
        }
        if ((double)rand() / RAND_MAX < prob_truck) {
            truck_queue.enQueue(current_time);
        }

        // Load the ferry
        if (current_time % ferry_interval == 0) {
            int num_loaded = 0;
            int num_car_loaded = 0;

            while (num_loaded < ferry_capacity && !(car_queue.isEmpty() && truck_queue.isEmpty())) {
                // Load 4 cars
                if (num_car_loaded < 4 && !car_queue.isEmpty()) {
                    int arrival_time = car_queue.deQueue();
                    int interval = current_time - arrival_time;
                    ++car_count;
                    car_time += interval;
                    ++num_loaded;
                    ++num_car_loaded;
                }

                // For every 4 cars, load 1 truck
                else if (num_car_loaded == 4 && !truck_queue.isEmpty()) {
                    int arrival_time = truck_queue.deQueue();
                    int interval = current_time - arrival_time;
                    ++truck_count;
                    truck_time += interval;
                    ++num_loaded;
                    num_car_loaded = 0;
                }

                // If there are no trucks, load cars
                else if (!car_queue.isEmpty() && truck_queue.isEmpty()) {
                    int arrival_time = car_queue.deQueue();
                    int interval = current_time - arrival_time;
                    ++car_count;
                    car_time += interval;
                    ++num_loaded;
                }

                // If there are no cars, load trucks
                else if (car_queue.isEmpty() && !truck_queue.isEmpty()) {
                    int arrival_time = truck_queue.deQueue();
                    int interval = current_time - arrival_time;
                    ++truck_count;
                    truck_time += interval;
                    ++num_loaded;
                }
            }
        }

        ++current_time;
    }

    cout << "Total cars transported: " << car_count << endl;
    cout << "Total trucks transported: " << truck_count << endl;
    cout << "Average waiting time for cars: ";
    cout << (double)car_time / car_count << " minutes" << endl;
    cout << "Average waiting time for trucks: ";
    cout << (double)truck_time / truck_count << " minutes" << endl;
}


int main() {
    srand(time(NULL));  // Seed for random number generator

    cout << "Please enter the simulation time (in minutes) : ";
    int simulation_time;
    cin >> simulation_time;

    cout << "Please enter the probability of a car arriving (0.0 - 1.0) : ";
    double prob_car;
    cin >> prob_car;

    cout << "Please enter the probability of a truck arriving (0.0 - 1.0) : ";
    double prob_truck;
    cin >> prob_truck;

    simulate_ferry_loading(simulation_time, prob_car, prob_truck);

    return 0;
}