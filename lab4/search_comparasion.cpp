#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace chrono;

// Binary Search 
int binarySearch(const vector<int>& arr, int key) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Interpolation Search 
int interpolationSearch(const vector<int>& arr, int key) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }
        // Interpolation formula
        int pos = low + (int)(((double)(key - arr[low]) / (arr[high] - arr[low])) * (high - low));
        if (arr[pos] == key) return pos;
        else if (arr[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

int main() {
    srand(time(0));
    const int N = 10000000;

    cout << "Generating " << N << " random numbers..." << endl;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) arr[i] = rand();

    cout << "Sorting array..." << endl;
    sort(arr.begin(), arr.end()); // Both searches require a sorted array

    // Pick a key guaranteed to exist
    int key = arr[N / 2];
    cout << "Searching for key: " << key << endl << endl;

    // Binary Search
    auto start = high_resolution_clock::now();
    int idxBin = binarySearch(arr, key);
    auto end = high_resolution_clock::now();
    double timeBin = duration<double, micro>(end - start).count();

    cout << "Binary Search:" << endl;
    cout << "  Index found : " << idxBin << endl;
    cout << "  Time        : " << timeBin << " microseconds" << endl << endl;

    // Interpolation Search
    start = high_resolution_clock::now();
    int idxInt = interpolationSearch(arr, key);
    end = high_resolution_clock::now();
    double timeInt = duration<double, micro>(end - start).count();

    cout << "Interpolation Search:" << endl;
    cout << "  Index found : " << idxInt << endl;
    cout << "  Time        : " << timeInt << " microseconds" << endl << endl;

    cout << "Speedup (Binary/Interpolation): " << timeBin / timeInt << "x" << endl;

    return 0;
}