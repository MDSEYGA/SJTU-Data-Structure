#include <iostream>
using namespace std;

template <class Type>
class CloseHashTable {
private:
    struct node {
        Type data;
        int state; // 0: empty, 1: occupied, 2: deleted
        node() : state(0) {}
    };

    node* array;
    int size;
    int key(const Type& x) const;
public:
    CloseHashTable(int length = 101, int deleted_threshold = INT_MAX);
    ~CloseHashTable() { delete[] array; };
    Type* find(const Type& x) const;
    void insert(const Type& x);
    void remove(const Type& x);

private:
    int occupied_count;
    int deleted_count;
    int deleted_threshold;
    int next_prime(int n);
    void double_space();
    void rehash();
    void auto_rehash();

public:
    void display() const;
};

template <class Type>
CloseHashTable<Type>::CloseHashTable(int length, int deleted_threshold) : size(length),  deleted_threshold(deleted_threshold), occupied_count(0), deleted_count(0) {
    array = new node[size];
}

template <class Type>
int CloseHashTable<Type>::key(const Type& x) const {
    return x % size; // Simple hash function: modulo size
}

template <class Type>
void CloseHashTable<Type>::insert(const Type& x) {
    int initPos, pos;

    initPos = pos = key(x);
    do {
        // Avoid inserting duplicates
        if (array[pos].state == 1 && array[pos].data == x)
            return;

        if (array[pos].state != 1) {
            array[pos].data = x;
            array[pos].state = 1;
            occupied_count++;
            auto_rehash();
            return;
        }

        pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <class Type>
void CloseHashTable<Type>::remove(const Type& x) {
    int initPos, pos;

    initPos = pos = key(x);
    do {
        if (array[pos].state == 0) return;
        if (array[pos].state == 1 && array[pos].data == x) {
            array[pos].state = 2;
            deleted_count++;
            auto_rehash();
            return;
        }

        pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <class Type>
Type* CloseHashTable<Type>::find(const Type& x) const {
    int initPos, pos;

    initPos = pos = key(x);
    do {
        if (array[pos].state == 0) return nullptr;
        if (array[pos].state == 1 && array[pos].data == x) return &array[pos].data;
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return nullptr;
}

template <class Type>
int CloseHashTable<Type>::next_prime(int n) {
    while (true) {
        bool is_prime = true;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) return n;
        ++n;
    }
}

/**
 * @brief Doubles the size of the hash table and re-inserts all occupied elements.
 * The new size is the smallest prime number greater than twice the old size.
 * This is triggered when the number of occupied slots exceeds half the table size.
 */
template <class Type>
void CloseHashTable<Type>::double_space() {
    node* tmp = array;
    int old_size = size;
    size = next_prime(old_size * 2);
    deleted_count = 0;
    occupied_count = 0;
    array = new node[size];

    // Reinsert all occupied entries
    for (int i = 0; i < old_size; i++) {
        if (tmp[i].state == 1) insert(tmp[i].data);
    }
    delete[] tmp;

    cout << endl << "Resized from " << old_size << " to " << size << "." << endl << endl;
}

/**
 * @brief Rehash all occupied elements into a fresh table of the same size.
 * This is triggered when the number of deleted slots exceeds the threshold.
 */
template <class Type>
void CloseHashTable<Type>::rehash() {
    deleted_count = 0;
    occupied_count = 0;
    node* tmp = array;
    array = new node[size];

    // Reinsert all valid entries
    for (int i = 0; i < size; ++i) {
        if (tmp[i].state == 1) insert(tmp[i].data);
    }
    delete[] tmp;

    cout << endl << "Rehashed." << endl << endl;
}

/**
 * @brief Checks if resizing or rehashing is necessary based on current load.
 * Triggers `double_space()` or `rehash()` accordingly.
 */
template <class Type>
void CloseHashTable<Type>::auto_rehash() {
    if (occupied_count > size / 2) {
        double_space();
    }
    if (deleted_count >= deleted_threshold) {
        rehash();
    }
}

template <class Type>
void CloseHashTable<Type>::display() const {
    cout << "Current Hash Table State (size = " << size << "):" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "[" << i << "]: ";
        if (array[i].state == 0) {
            cout << "EMPTY" << endl;
        } else if (array[i].state == 1) {
            cout << array[i].data << " (OCCUPIED)" << endl;
        } else if (array[i].state == 2) {
            cout << "DELETED" << endl;
        }
    }
    cout << endl;
}

int main() {
    int size;
    int deleted_threshold;

    cout << "Enter initial size of hash table: ";
    cin >> size;

    cout << "Enter deleted threshold: ";
    cin >> deleted_threshold;

    CloseHashTable<int> table(size, deleted_threshold);

    int choice, value;
    cout << "1: insert, 2: remove, 3: find, 0: exit" << endl;

    while (true) {
        cout << endl << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;

        cout << "Enter value: ";
        cin >> value;

        if (choice == 1) {
            table.insert(value);
        } else if (choice == 2) {
            table.remove(value);
        } else if (choice == 3) {
            int* res = table.find(value);
            if (res != nullptr) {
                cout << "Found: " << *res << endl;
            } else {
                cout << "Not found." << endl;
            }
        }

        table.display();
    }

    return 0;
}
