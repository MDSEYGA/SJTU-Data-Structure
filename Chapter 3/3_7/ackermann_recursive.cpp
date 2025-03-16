#include <iostream>
using namespace std;

/**
 * Recursive implementation of the Ackermann function
 */
int ackermannRecursive(int m, int n) {
    if (m == 0) {
      return n + 1;
    }

    if (m > 0 && n == 0) {
      return ackermannRecursive(m - 1, 1);
    }

    return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
}

int main() {
    int m, n;
    cout << "Enter values for m and n: ";
    cin >> m >> n;
    
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermannRecursive(m, n) << endl;
    return 0;
}
