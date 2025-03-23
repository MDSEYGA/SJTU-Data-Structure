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
    int car_num = 0, truck_num = 0;
    int car_time = 0, truck_time = 0;
    
    while (current_time < simulation_time) {
        if ((double)rand() / RAND_MAX < prob_car) {
            car_queue.enQueue(current_time);
        }
        if ((double)rand() / RAND_MAX < prob_truck) {
            truck_queue.enQueue(current_time);
        }
    }

    if (current_time % ferry_interval == 0) {
        int num_loaded = 0;

        while (num_loaded < ferry_capacity && !(car_queue.isEmpty() && truck_queue.isEmpty())) {
            int num_car_loaded = 0;

            if (num_car_loaded < 4 && !car_queue.isEmpty()) {
                int arrival_time = car_queue.deQueue();
                int interval = current_time - arrival_time;
                ++car_num;
                car_time += interval;
                ++num_loaded;
                ++num_car_loaded;
            }

            else if (num_car_loaded = 4 && !truck_queue.isEmpty()) {
                int arrival_time = truck_queue.deQueue();
                int interval = current_time - arrival_time;
                ++truck_num;
                truck_time += interval;
                ++num_loaded;
                num_car_loaded = 0;
            }

            else if (num_car_loaded = 4 && truck_queue.isEmpty() && !car_queue.isEmpty()) {
                int arrival_time = car_queue.deQueue();
                int interval = current_time - arrival_time;
                ++car_num;
                car_time += interval;
                ++num_loaded;
            }

            else if (num_car_loaded < 4 && car_queue.isEmpty() && !truck_queue.isEmpty()) {
                int arrival_time = truck_queue.deQueue();
                int interval = current_time - arrival_time;
                ++truck_num;
                truck_time += interval;
                ++num_loaded;
                ++num_car_loaded;
            }
        }
    }


    ++current_time;
}


int main() {
    srand(time(NULL));  // seed for random number generator
}