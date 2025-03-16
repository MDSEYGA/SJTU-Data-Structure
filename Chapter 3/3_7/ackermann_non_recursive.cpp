#include <iostream>
#include <fstream>
using namespace std;

template <class elemType>
class Stack {
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~Stack() {}
};

template <class elemType>
class linkStack:public Stack<elemType> {
private:
    struct node{
        elemType data;
        node* next;

        node(const elemType &x, node* N = nullptr) : data(x), next(N) {}
        node() : next(nullptr) {}
        ~node() {}
    };

    node* top_p;

public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};

template <class elemType>
linkStack<elemType>::linkStack() {
    top_p = nullptr;
}

template <class elemType>
linkStack<elemType>::~linkStack() {
    node* tmp;
    while (top_p != nullptr) {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const {
    return top_p == nullptr;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x) {
    top_p = new node(x, top_p);
}

template <class elemType>
elemType linkStack<elemType>::pop() {
    node* tmp = top_p;
    elemType x = tmp->data;
    top_p = top_p->next;
    delete tmp;
    return x;
}

template <class elemType>
elemType linkStack<elemType>::top() const {
    return top_p->data;
}

/**
 * Struct to represent a (m, n) pair in the stack
 */
struct Pair {
    int first;
    int second;
    Pair(int first, int second) : first(first), second(second) {}
};

/**
 * Non-Recursive implementation of the Ackermann function
 */
int ackermannNonRecursive(int m, int n) {
    linkStack<Pair> stack;
    stack.push(Pair(m, n));

    while (!stack.isEmpty()) {
        Pair p = stack.pop();
        m = p.first;
        n = p.second;

        if (m == 0) {
            // If the stack is not empty, update n of the next pair in the stack
            if (!stack.isEmpty()) {
                Pair p = stack.top();
                stack.pop();
                m = p.first;
                n = n + 1;
                stack.push(Pair(m, n));
            }

            // If the stack is empty, return n + 1 as the final result
            else {
                return n + 1;
            }
        }

        else if (m > 0 && n == 0) {
            stack.push(Pair(m - 1, 1));
        }

        else {
            stack.push(Pair(m - 1, -1));
            stack.push(Pair(m, n - 1));
        }
    }
}

int main() {
    int m, n;
    cout << "Enter values for m and n: ";
    cin >> m >> n;
    
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermannNonRecursive(m, n) << endl;
    return 0;
}