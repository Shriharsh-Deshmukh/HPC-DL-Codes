#include <iostream>
#include <omp.h>
using namespace std;

// Function to perform vector addition
void vectorAddition(int a[], int b[], int c[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int n;
    cout << "Enter the size of the vectors: ";
    cin >> n;

    int a[n], b[n], c[n];

    cout << "Enter elements of first vector:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << "Enter elements of second vector:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    // Call the function to add vectors
    vectorAddition(a, b, c, n);

    cout << "Resultant vector after addition:" << endl;
    for (int i = 0; i < n; i++) {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}

// g++ -fopenmp -o vector_add 1_Vector_addition.cpp
// ./vector_add
