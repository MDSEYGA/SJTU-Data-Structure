#include <iostream>
using namespace std;

template <class elemType>
class Queue {
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~Queue() {}
};

template <class elemType>
class linkQueue: public Queue<elemType> {
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

template <class Type>
class PriorityQueue:public Queue<Type> {
public:
    PriorityQueue(int capacity=100);
    PriorityQueue(const Type data[], int size);
    ~PriorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
    Type search(int i) const;
    void display() const;

private:
    int currentSize;
    Type* Array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
    void percolateUp(int hole);

public:
    int findMin(int x);
    void decreaseKey(int i, int value);
};

template <class Type>
PriorityQueue<Type>::PriorityQueue(int capacity) {
    Array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template <class Type>
PriorityQueue<Type>::~PriorityQueue() {
    delete [] Array;
}

template <class Type>
bool PriorityQueue<Type>::isEmpty() const {
    return currentSize == 0;
}

template <class Type>
Type PriorityQueue<Type>::getHead() const {
    return Array[1];
}

template <class Type>
void PriorityQueue<Type>::enQueue(const Type &x) {
    if (currentSize == maxSize - 1) {
        doubleSpace();
    }
    int hole = ++currentSize;
    for (; hole > 1 && x < Array[hole / 2]; hole /= 2) {
        Array[hole] = Array[hole / 2];
    }
    Array[hole] = x;
}

template <class Type>
Type PriorityQueue<Type>::deQueue() {
    Type minItem;
    minItem = Array[1];
    Array[1] = Array[currentSize--];
    percolateDown(1);
    return minItem;
}

template <class Type>
void PriorityQueue<Type>::percolateDown(int hole) {
    int child;
    Type tmp = Array[hole];
    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child != currentSize && Array[child + 1] < Array[child]) {
            ++child;
        }
        if (Array[child] < tmp) {
            Array[hole] = Array[child];
        } else {
            break;
        }
    }
    Array[hole] = tmp;
}

template <class Type>
void PriorityQueue<Type>::buildHeap() {
    for (int i = currentSize / 2; i > 0; --i) {
        percolateDown(i);
    }
}

template <class Type>
PriorityQueue<Type>::PriorityQueue(const Type* items, int size): maxSize(size + 10), currentSize(size) {
    Array = new Type[maxSize];
    for (int i = 0; i < size; ++i) {
        Array[i + 1] = items[i];
    }
    buildHeap();
}

template <class Type>
void PriorityQueue<Type>::doubleSpace() {
    Type* tmp = Array;
    maxSize *= 2;
    Array = new Type[maxSize];
    for (int i = 0; i <= currentSize; ++i) {
        Array[i] = tmp[i];
    }
    delete [] tmp;
}

template <class Type>
Type PriorityQueue<Type>::search(int i) const {
    return Array[i];
}

template <class Type>
void PriorityQueue<Type>::display() const {
    for (int i = 1; i <= currentSize; ++i) {
        cout << Array[i] << " ";
    }
    cout << endl;
}

/**
 * @brief Finds the index of the minimum element in the heap that is greater than a given value x.
 *
 * @return The index of the minimum element greater than x. 
 *
 * @note Although a more efficient approach using BFS with branch pruning exists,
 *       for simplicity, a full traversal is used here.
 */
template <class Type>
int PriorityQueue<Type>::findMin(int x) {
    int min = INT_MAX;
    int index = -1;
    for (int i = 1; i <= currentSize; ++i) {
        if (Array[i] < min && Array[i] > x) {
            min = Array[i];
            index = i;
        }
    }
    return index;
}

/**
 * @brief Moves an element at the given position upward to restore the heap property.
 *
 * @note This is a helper function for decreaseKey(),
 */
template <class Type>
void PriorityQueue<Type>::percolateUp(int hole) {
    Type x = Array[hole];
    // Move the hole upward until the heap property is restored
    for (; hole > 1 && x < Array[hole / 2]; hole /= 2) {
        Array[hole] = Array[hole / 2];  // Move the parent down
    }
    Array[hole] = x;
}

/**
 * @brief Decreases the key of an element at a given index by a certain value, and restores the heap property.
 */
template <class Type>
void PriorityQueue<Type>::decreaseKey(int i, int value) {
    Array[i] -= value;
    percolateUp(i);
}

int main() {
    int size;
    cout << "Please enter the number of elements: ";
    cin >> size;
    
    int* arr = new int[size];
    cout << "Please enter the elements: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
    PriorityQueue<int> pq(arr, size);
    cout << "The elements in the priority queue are: ";
    pq.display();

    cout << "Please enter x for findMin(x): ";
    int x;
    cin >> x;
    cout << "The minimum element greater than " << x << " is: " << pq.search(pq.findMin(x)) << " at index " << pq.findMin(x) << endl;

    int i, value;
    cout << "Please enter i and value for decreaseKey(i, value): ";
    cin >> i >> value;
    cout << "Decreasing the key of element at index " << i << " by " << value << "." << endl;
    pq.decreaseKey(i, value);
    cout << "The elements in the priority queue after decreaseKey are: ";
    pq.display();

    delete[] arr;
    return 0;
}