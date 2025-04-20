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
class binaryTree {
    friend void printTree(const binaryTree<T> &t, T flag);

private:
    struct Node {
        Node* left;
        Node* right;
        T data;

        Node(): left(nullptr), right(nullptr) {}

        Node(T item, Node* L = nullptr, Node* R = nullptr): data(item), left(L), right(R) {}

        ~Node() {}
    };

    Node* root;

public:
    binaryTree(): root(nullptr) {}
    binaryTree(T x) {
        root = new Node(x);
    }
    ~binaryTree();
    void clear();
    bool isEmpty() const;
    T Root(T flag) const;
    T lchild(T x, T flag) const;
    T rchild(T x, T flag) const;
    void delLeft(T x);
    void delRight(T x);
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    void createTree(T flag);
    T parent (T x, T flag) const {
        return flag;
    }

private:
    void clear(Node*& t);
    void preOrder(Node* t) const;
    void midOrder(Node* t) const;
    void postOrder(Node* t) const;

public:
    int degree_two_count();
};

template <class T>
bool binaryTree<T>::isEmpty() const {
    return root == nullptr;
}

template <class T>
T binaryTree<T>::Root(T flag) const {
    if (root == nullptr) return flag;
    else return root->data;
}

template <class T>
void binaryTree<T>::clear(binaryTree<T>::Node*& t) {
    if (t == nullptr) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = nullptr;
}

template <class T>
void binaryTree<T>::clear() {
    clear(root);
}

template <class T>
binaryTree<T>::~binaryTree() {
    clear(root);
}

template <class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node* t) const {
    if (t == nullptr) return;
    cout << t->data << ' ';
    preOrder(t->left);
    preOrder(t->right);
}

template <class T>
void binaryTree<T>::preOrder() const {
    cout << "\nPre-order traversal: ";
    preOrder(root);
}

template <class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node* t) const {
    if (t == nullptr) return;
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}

template <class T>
void binaryTree<T>::midOrder() const {
    cout << "\nMid-order traversal: ";
    midOrder(root);
}

template <class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node* t) const {
    if (t == nullptr) return;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << ' ';
}

template <class T>
void binaryTree<T>::postOrder() const {
    cout << "\nPost-order traversal: ";
    postOrder(root);
}

template <class T>
void binaryTree<T>::levelOrder() const {
    linkQueue<Node*> que;
    Node* tmp;

    cout << "\nLevel-order traversal: ";
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
}

template <class T>
void binaryTree<T>::delLeft(T x) {
    Node* tmp = find(x, root);
    if (tmp == nullptr) return;
    clear(tmp->left);
}

template <class T>
void binaryTree<T>::delRight(T x) {
    Node* tmp = find(x, root);
    if (tmp == nullptr) return;
    clear(tmp->right);
}

template <class T>
T binaryTree<T>::lchild(T x, T flag) const {
    Node* tmp = find(x, root);
    if (tmp == nullptr || tmp->left == nullptr) return flag;
    return tmp->left->data;
}

template <class T>
T binaryTree<T>::rchild(T x, T flag) const {
    Node* tmp = find(x, root);
    if (tmp == nullptr || tmp->right == nullptr) return flag;
    return tmp->right->data;
}

template <class T>
void binaryTree<T>::createTree(T flag) {
    linkQueue<Node*> que;
    Node* tmp;
    T x, ldata, rdata;
    cout << "\nEnter root node: ";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << "\nEnter left and right children of " << tmp->data << ": ";
        cin >> ldata >> rdata;
        if (ldata != flag) que.enQueue(tmp->left = new Node(ldata));
        if (rdata != flag) que.enQueue(tmp->right = new Node(rdata));
    }

    cout << "Tree creation completed!\n";
}

template <class T>
void printTree(const binaryTree<T>& t, T flag) {
    linkQueue<T> q;
    q.enQueue(t.root->data);
    cout << endl;
    while (!q.isEmpty()) {
        char p, l, r;
        p = q.deQueue();
        l = t.lchild(p, flag);
        r = t.rchild(p, flag);
        cout << p << ' ' << l << ' ' << r << endl;
        if (l != '@') q.enQueue(l);
        if (r != '@') q.enQueue(r);
    }
}

/**
 * Counts the number of nodes in the binary tree that have exactly two children.
 * A node is considered to have degree 2 if both its left and right children are non-null.
 *
 * @return The count of nodes with degree 2 in the binary tree.
 */
template <class T>
int binaryTree<T>::degree_two_count() {
    int count = 0;
    linkQueue<Node*> que;
    Node* tmp;
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        if (tmp->left != nullptr && tmp->right != nullptr) {
            ++count;
        }
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }

    return count;
}

int main() {
    binaryTree<char> tree;
    char flag = '@';
    tree.createTree(flag);

    tree.preOrder();
    tree.midOrder();
    tree.postOrder();

    cout << endl << "Number of 2-degree nodes: " << tree.degree_two_count() << endl;

    return 0;
}