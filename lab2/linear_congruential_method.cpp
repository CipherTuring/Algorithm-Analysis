#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// LCG Algorithm
vector<long long> generateLCG(int n, long long seed, long long a, long long c, long long m) {
    vector<long long> random_numbers;
    random_numbers.reserve(n); 
    
    long long x = seed;
    for (int i = 0; i < n; i++) {
        x = (a * x + c) % m; // basic operation
        random_numbers.push_back(x);
    }
    return random_numbers;
}

int main() {
    // Parameters
    long long m = 2147483648; // 2^31
    long long a = 1103515245;
    long long c = 12345;
    long long seed = 42;

    cout << "n,time_milliseconds\n";

    // Test for n: from 10 million to 50 million
    for (int n = 10000000; n <= 200000000; n += 10000000) {
        
        auto start = high_resolution_clock::now();
        
        generateLCG(n, seed, a, c, m);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        
        cout << n << "," << duration.count() << "\n";
    }

    return 0;
}