#include <iostream>
using namespace std;

void percolate_down(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        percolate_down(arr, n, smallest);
    }
}

void percolate_up(int arr[], int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (arr[i] < arr[parent]) {
            swap(arr[i], arr[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

void push(int arr[], int &n, int value) {
    arr[n] = value; // Insert the new element at the end
    n++;
    percolate_up(arr, n - 1);
}

int pop(int arr[], int &n) {
    int root = arr[0];
    arr[0] = arr[n - 1]; // Move the last element to root
    n--;

    percolate_down(arr, n, 0);
    return root;
}

void replace_top(int arr[], int n, int value) {
    arr[0] = value; // Replace the root with the new value
    percolate_down(arr, n, 0);
}

/**
 * @brief Finds the kth largest element in an array using a min heap.
 * The time complexity is O(N log k).
 */
int find_kth_largest(int arr[], int n, int k) {
    int heap[k]; // Create a min heap of size k
    int size = 0;

    for (int i = 0; i < n; ++i) {
        if (size < k) {
            push(heap, size, arr[i]); // Push the current element into the heap, time complexity O(log k)
        } else if (arr[i] > heap[0]) {
            replace_top(heap, size, arr[i]); // Replace the smallest element in the heap, time complexity O(log k)
        }
    }

    return heap[0]; // The kth largest element
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