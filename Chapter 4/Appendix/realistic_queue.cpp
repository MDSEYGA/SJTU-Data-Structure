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

class Simulator {
    int arrival_low;
    int arrival_high;
    int service_time_low;
    int service_time_high;
    int custom_num;

public:
    Simulator();
    int avgWaitTime() const;
};

Simulator::Simulator() {
    cout << "Enter the range of arrival time (low high): ";
    cin >> arrival_low >> arrival_high;

    cout << "Enter the range of service time (low high): ";
    cin >> service_time_low >> service_time_high;

    cout << "Enter the number of customers: ";
    cin >> custom_num;

    srand(time(0));
}

int Simulator::avgWaitTime() const {
    int current_time = 0;
    int total_wait_time = 0;
    int next_arrival_time = 0;

    linkQueue<int> customer_queue;

    for (int i = 0; i < custom_num; ++i) {
        // Generate next arrival
        next_arrival_time += (rand() % (arrival_high - arrival_low + 1)) + arrival_low;

        // Check if server is free
        if (next_arrival_time >= current_time) {
            // No queue, serve immediately
            current_time = next_arrival_time + (rand() % (service_time_high - service_time_low + 1)) + service_time_low;
        } else {
            // Customer joins the queue
            customer_queue.enQueue(next_arrival_time);
        }

        // Serve queued customers
        while (!customer_queue.isEmpty() && customer_queue.getHead() <= current_time) {
            int waitTime = current_time - customer_queue.deQueue();
            total_wait_time += waitTime;
            current_time += (rand() % (service_time_high - service_time_low + 1)) + service_time_low;
        }
    }

    return total_wait_time / custom_num;
}

int main() {
    Simulator sim;
    cout << "Average wait time: " << sim.avgWaitTime() << endl;
    return 0;
}