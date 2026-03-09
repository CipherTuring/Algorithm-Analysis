#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

int knapsackExhaustive(int n, vector<int>& weights, vector<int>& values, int capacity) {
    int bestValue = 0;
    long long subsets = 1LL << n; 

    for(long long mask = 0; mask < subsets; mask++) {
        int totalWeight = 0;
        int totalValue = 0;

        for(int i = 0; i < n; i++) {
            if(mask & (1LL << i)) {
                totalWeight += weights[i];
                totalValue += values[i];
            }
        }

        if(totalWeight <= capacity && totalValue > bestValue)
            bestValue = totalValue;
    }
    return bestValue; 
}

int main() {
    srand(time(0));

    cout << "n\tTime(seconds)" << endl;
    cout << "-----------------------" << endl;

    for(int n = 4; ; n++) {
        vector<int> weights(n);
        vector<int> values(n);

        for(int i = 0; i < n; i++) {
            weights[i] = rand() % 20 + 1;
            values[i] = rand() % 50 + 1;
        }

        int capacity = n * 10;

        auto start = high_resolution_clock::now();
        knapsackExhaustive(n, weights, values, capacity);
        auto stop = high_resolution_clock::now();

        duration<double> elapsed = stop - start;

        if(elapsed.count() > 600) {
            cout << "\n[!] n=" << n << " took more than the limit of 10 minutes" << endl;
            break;
        }

        cout << n << "\t" << elapsed.count() << endl;
    }

    return 0;
}