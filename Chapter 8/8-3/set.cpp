#include <iostream>
using namespace std;

template <class T>
class Set {
private:
    T* elements;
    int size;
    int capacity;

    void doubleCapacity() {
        capacity *= 2;
        T* newElements = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

    bool contains(const T& value) const {
        for (int i = 0; i < size; ++i) {
            if (elements[i] == value) {
                return true;
            }
        }
        return false;
    }

public:
    Set(int cap = 10) {
        capacity = cap;
        size = 0;
        elements = new T[capacity];
    }

    Set(const Set& other) {
        capacity = other.capacity;
        size = other.size;
        elements = new T[capacity];
        for (int i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    ~Set() {
        delete[] elements;
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    void insert(const T& value) {
        if (!contains(value)) {
            if (size == capacity) {
                doubleCapacity();
            }
            elements[size] = value;
            size++;
        }
    }

    Set operator+(const Set& other) const {
        Set result(*this);
        for (int i = 0; i < other.size; ++i) {
            result.insert(other.elements[i]);
        }
        return result;
    }

    Set operator*(const Set& other) const {
        Set result;
        for (int i = 0; i < size; ++i) {
            if (other.contains(elements[i])) {
                result.insert(elements[i]);
            }
        }
        return result;
    }

    Set operator-(const Set& other) const {
        Set result;
        for (int i = 0; i < size; ++i) {
            if (!other.contains(elements[i])) {
                result.insert(elements[i]);
            }
        }
        return result;
    }

    void display() const {
        cout << "{ ";
        for (int i = 0; i < size; ++i) {
            cout << elements[i] << " ";
        }
        cout << "}" << endl;
    }
};

int main() {
    Set<int> A, B;
    A.insert(1);
    A.insert(2);
    A.insert(3);

    B.insert(3);
    B.insert(4);
    B.insert(5);

    cout << "Set A: ";
    A.display();
    cout << "Set B: ";
    B.display();

    Set<int> C = A + B;
    cout << "A + B (Union): ";
    C.display();

    Set<int> D = A * B;
    cout << "A * B (Intersection): ";
    D.display();

    Set<int> E = A - B;
    cout << "A - B (Difference): ";
    E.display();

    return 0;
}
