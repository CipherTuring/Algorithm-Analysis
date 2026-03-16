#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void insertionSort(char arr[], int n) {
    for (int i = 1; i < n; i++) {
        char key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(0));
    const int N = 20;
    char arr[N];

    // Generate random lowercase alphabetic characters
    for (int i = 0; i < N; i++) {
        arr[i] = 'a' + rand() % 26;
    }

    cout << "Original array: ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    insertionSort(arr, N);

    cout << "Sorted array:   ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}