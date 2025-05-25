#include <iostream>
using namespace std;

void percolate_down(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        percolate_down(arr, n, largest);
    }
}

void build_max_heap(int arr[], int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--)
        percolate_down(arr, n, i);
}

int pop(int arr[], int &n) {
    int root = arr[0];
    arr[0] = arr[n - 1]; // Move the last element to root
    n--;

    percolate_down(arr, n, 0);
    return root;
}

/**
 * @brief Finds the kth largest element in an array using a max heap.
 * The time complexity is O(N + k log N).
 */
int find_kth_largest(int arr[], int n, int k) {
    build_max_heap(arr, n); // Build max heap, time complexity O(N)

    for (int i = 0; i < k - 1; i++) {
        pop(arr, n); // Pop the largest element k-1 times, time complexity O(log N)
    }

    return pop(arr, n); // The kth largest element
}

int main() {
    int size;
    cout << "Please enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Please enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    int k;
    cout << "Please enter the value of k: ";
    cin >> k;

    cout << "The " << k << "th largest element is: " << find_kth_largest(arr, size, k) << endl;
    delete[] arr;

    return 0;
}