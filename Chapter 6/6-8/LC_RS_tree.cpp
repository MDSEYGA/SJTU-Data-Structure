#include <iostream>
#include <ctime>
#include <stdlib.h>
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

template <class T>
class Tree {
private:
    struct Node {
        Node* son;
        Node* brother;
        T data;

        Node(): son(nullptr), brother(nullptr) {}

        Node(T item, Node* son = nullptr, Node* brother = nullptr): data(item), son(son), brother(brother) {}

        ~Node() {}
    };

    Node* root;

public:
    Tree(): root(nullptr) {}
    Tree(T x) {
        root = new Node(x);
    }
    ~Tree();
    void clear();
    void preOrder() const;
    void postOrder() const;
    void levelOrder() const;
    void createTree(T flag);

private:
    void clear(Node*& t);
    void preOrder(Node* t) const;
    void postOrder(Node* t) const;
    void levelOrder(Node* t) const;
};

template <class T>
void Tree<T>::clear(Tree<T>::Node*& t) {
    if (t == nullptr) return;
    clear(t->son);
    clear(t->brother);
    delete t;
    t = nullptr;
}

template <class T>
void Tree<T>::clear() {
    clear(root);
}

template <class T>
Tree<T>::~Tree() {
    clear(root);
}

// Pre-order traversal for a left-child right-sibling tree
template <class T>
void Tree<T>::preOrder(Tree<T>::Node* t) const {
    if (t == nullptr) return;
    cout << t->data << ' ';
    preOrder(t->son);
    preOrder(t->brother);
}

template <class T>
void Tree<T>::preOrder() const {
    cout << "\nPre-order traversal: ";
    preOrder(root);
}

// Post-order traversal for a left-child right-sibling tree
template <class T>
void Tree<T>::postOrder(Tree<T>::Node* t) const {
    if (t == nullptr) return;
    postOrder(t->son);
    cout << t->data << ' ';
    postOrder(t->brother);
}

template <class T>
void Tree<T>::postOrder() const {
    cout << "\nPost-order traversal: ";
    postOrder(root);
}

// Level-order traversal for a left-child right-sibling tree
template <class T>
void Tree<T>::levelOrder(Tree<T>::Node* t) const {
    linkQueue<Node*> que;
    Node* tmp;

    que.enQueue(t);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->son) que.enQueue(tmp->son);
        while (tmp->brother) {  // Iterate through brothers
            tmp = tmp->brother;
            cout << tmp->data << ' ';
            if (tmp->son) que.enQueue(tmp->son);
        }
    }
}

template <class T>
void Tree<T>::levelOrder() const {
    cout << "\nLevel-order traversal: ";
    levelOrder(root);
}

// Create a left-child right-sibling tree
template <class T>
void Tree<T>::createTree(T flag) {
    linkQueue<Node*> que;
    Node* tmp;
    T x, son;
    cout << "\nEnter root node: ";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << "\nEnter all the children of " << tmp->data << " ( End with " << flag << " ) : ";
        cin >> son;
        if (son == flag) continue;
        tmp->son = new Node(son);
        tmp = tmp->son;
        que.enQueue(tmp);
        while (true) {
            cin >> son;
            if (son == flag) break;
            tmp->brother = new Node(son);
            tmp = tmp->brother;
            que.enQueue(tmp);
        }
    }

    cout << "Tree creation completed!\n";
}

int main()
{
    Tree<char> tree;
    tree.createTree('@');

    tree.preOrder();
    tree.postOrder();
    tree.levelOrder();

    return 0;
}

