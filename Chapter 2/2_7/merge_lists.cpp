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
class seqList: public List<elemType>{
private:
    elemType* data;
    int currentLength;
    int maxSize;
    void doubleSpace();

public:
    seqList(int initSize = 10);
    ~seqList();
    void clear();
    int length() const;
    void insert(int i, const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;

    // The operator +
    seqList<elemType> operator+(const seqList<elemType> &b) const;
};


template <class elemType>
seqList<elemType>::~seqList() {
    delete [] data;
}

template <class elemType>
void seqList<elemType>::clear() {
    currentLength = 0;
}

template <class elemType>
int seqList<elemType>::length() const {
    return currentLength;
}

template <class elemType>
elemType seqList<elemType>::visit(int i) const {
    return data[i];
}

template <class elemType>
void seqList<elemType>::traverse() const {
    for (int i = 0; i < currentLength; ++i)
        cout << data[i] << ' ';
    cout << endl;
}

template <class elemType>
seqList<elemType>::seqList(int initSize) {
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
int seqList<elemType>::search(const elemType &x) const {
    int i;

    for (i = 0; i < currentLength && data[i] != x; ++i);

    if (i == currentLength) {
        return -1;
    } else {
        return i;
    }
}

template <class elemType>
void seqList<elemType>::doubleSpace() {
    elemType* tmp = data;

    maxSize *= 2;
    data = new elemType[maxSize];
    for (int i = 0; i < currentLength; ++i)
        data[i] = tmp[i];
    delete [] tmp;
}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x) {
    if (currentLength == maxSize) {
        doubleSpace();
    }

    for (int j = currentLength; j > i; j--) {
        data[j]=data[j-1];
    }

    data[i] = x;
    ++currentLength;
}

template <class elemType>
void seqList<elemType>::remove(int i) {
    for (int j = i; j < currentLength - 1; j++) {
        data[j] = data[j + 1];
    }

    --currentLength;
}


/**
 * @brief Merges two sequential lists using the '+' operator.
 *
 * This function creates a new list that contains all elements
 * from the current list (`this` list) followed by all elements
 * from list `B`. The original lists remain unchanged.  
 */
template<class elemType>
seqList<elemType> seqList<elemType>::operator+(const seqList<elemType> &B) const {
    seqList<elemType> C(currentLength + B.currentLength);  // Create a new list with enough space for all elements from both lists
    C.currentLength = currentLength + B.currentLength;  // Set the currentLength for the new list

    for (int i = 0; i < currentLength; ++i) { 
        C.data[i] = data[i];  // Copy elements from the first list 'this' into the new list
    }

    for (int i = currentLength; i < C.currentLength; ++i) {
        C.data[i] = B.data[i - currentLength];  // Copy elements from the second list 'B' into the new list
    }

    return C;  // Return the merged list
}


int main()
{
    seqList<int> A, B;
    int num, element;

    cout << "Please enter the number of int elements of list A: ";
    cin >> num;

    if (num > 0) {
        cout << "Please enter the int elements of list A: ";
        for (int i = 0; i < num; i++) {
            cin >> element;
            A.insert(i, element);
        }
    }

    cout << "Please enter the number of int elements of list B: ";
    cin >> num;

    if (num > 0) {
        cout << "Please enter the int elements of list B: ";
        for (int i = 0; i < num; i++) {
            cin >> element;
            B.insert(i, element);
        }
    }

    cout << "Two lists before linking: " << endl;
    cout << "List A: ";
    A.traverse();
    cout << "List B: ";
    B.traverse();

    seqList<int> C = A + B;

    cout << "The list after linking: " << endl;
    cout << "List C: ";
    C.traverse();

    return 0;
}
