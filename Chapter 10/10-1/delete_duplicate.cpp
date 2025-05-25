#include <iostream>
using namespace std;

template <class T>
int divide(T a[], int low, int high) {
    T k = a[low];
    do {
        while (low < high && a[high] >= k) {
            --high;
        }
        if (low < high) {
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low] <= k) {
            ++low;
        }
        if (low < high) {
            a[high] = a[low];
            --high;
        }
    } while (low != high);
    a[low] = k;
    return low;
}

template <class T>
void quickSort(T a[], int low, int high) {
    int mid;
    if (low >= high) {
        return;
    }
    mid = divide(a, low, high);
    quickSort(a, low, mid - 1);
    quickSort(a, mid + 1, high);
}

template <class T>
void quickSort(T a[], int size) {
    quickSort(a, 0, size - 1);
}

/**
 * @brief Deletes duplicate elements from an array and returns the number of unique elements.
 */
int delete_duplicate(int a[], int size) {
    quickSort(a, size);

    int num = 0;
    for (int i = 1; i < size; ++i) {
        if (a[i] != a[num]) {
            ++num;
            a[num] = a[i];
        }
    }
    ++num;

    for (int i = num; i < size; ++i) {
        a[i] = -1;  // -1 indicates the element is deleted
    }

    return num;
}

int main() {
    int size;
    cout << "Please enter the number of elements: ";
    cin >> size;

    int* a = new int[size];
    cout << "Please enter the elements: ";
    for (int i = 0; i < size; ++i) {
        cin >> a[i];
    }

    int num = delete_duplicate(a, size);
    cout << "The number of unique elements is: " << num << endl;

    cout << "The elements after deletion are: ";
    for (int i = 0; i < size; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    delete[] a;

    return 0;
}