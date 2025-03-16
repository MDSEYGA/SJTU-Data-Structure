#include <iostream>
using namespace std;

template <class elemType>
class List{
    public:
        virtual void clear() = 0;
        virtual int length() const = 0;
        virtual void insert(int i, const elemType &x) = 0;
        virtual void remove(int i) = 0;
        virtual int search(const elemType &x) const = 0;
        virtual elemType visit(int i) const = 0;
        virtual void traverse() const = 0;
        virtual ~List() {};
};

template <class elemType>
class sLinkList: public List<elemType>{
private:
    struct node{
        elemType data;
        node* next;

        node(const elemType &x, node* n = nullptr) : data(x), next(n) {}
        node() : next(nullptr) {}
        ~node() {}
    };
        
    node* head;
    int currentLength;

    node* move(int i) const;

public:
    sLinkList();
    ~sLinkList() {clear(); delete head;}

    void clear();
    int length() const {return currentLength;}
    void insert(int i, const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;

    // The reverse function
    void reverse();
};

template <class elemType>
typename sLinkList<elemType>::node* sLinkList<elemType>::move(int i) const {
    node* p = head;
    while (i > 0) {
        p = p->next;
        i--;
    }
    return p;
}

template<class elemType>
sLinkList<elemType>::sLinkList() {
    head = new node;
    currentLength = 0;
}

template<class elemType>
void sLinkList<elemType>::clear() {
    node* p = head->next;
    node* q;

    head->next = nullptr;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template<class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x) {
    node* pos;

    pos = move(i-1);
    pos->next = new node(x, pos->next);
    ++currentLength;
}

template<class elemType>
void sLinkList<elemType>::remove(int i) {
    node* pos;
    node* delp;

    pos = move(i - 1);
    delp = pos->next;
    pos->next = delp->next;
    delete delp;
    --currentLength;
}

template<class elemType>
int sLinkList<elemType>::search(const elemType &x) const {
    node* p = head->next;
    int i = 0;

    while (p != nullptr && p->data != x) {
        p = p->next;
        ++i;
    }

    if (p == nullptr) {
        return -1; 
    } else {
        return i; 
    }
}

template<class elemType>
elemType sLinkList<elemType>::visit(int i) const{
    return move(i)->data;
}

template<class elemType>
void sLinkList<elemType>::traverse() const{
    node* p = head->next;
    while (p != nullptr) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

/**
 * @brief Reverses the linked list.
 *
 * This function modifies the list by reversing the order of its nodes
 * without using additional memory. It runs in O(n) time complexity.
 */
template<class elemType>
void sLinkList<elemType>::reverse() {
    if (currentLength <= 1) {  // No need to reverse with empty and single-element lists
        return;
    }

    node* curr = head->next;
    node* next = nullptr;
    node* prev = nullptr;

    while (curr != nullptr) {
        next = curr->next;  // Store next node
        curr->next = prev;  // Reverse curr's pointer 
        prev = curr;  // Move prev forward
        curr = next;  // Move curr forward
    }

    head->next = prev;  // Update head
}

int main()
{
    sLinkList<int> list;
    int num, element;

    cout << "Please enter the number of int elements of the list: ";
    cin >> num;

    if (num > 0) {
        cout << "Please enter the int elements of the list: ";
        for (int i = 0; i < num; i++) {
            cin >> element;
            list.insert(i, element);
        }
    }

    cout << "List before reversing: "<< endl;
    list.traverse();

    list.reverse();

    cout << "List after reversing:" << endl;
    list.traverse();

    return 0;
}
