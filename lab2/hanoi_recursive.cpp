#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

unsigned long long hanoiRecursive(int n, char source, char target, char auxiliary) {
    if (n == 0) return 0;
    
    unsigned long long moves = 0;
    moves += hanoiRecursive(n - 1, source, auxiliary, target);
    moves++; // Count the movement
    moves += hanoiRecursive(n - 1, auxiliary, target, source);
    
    return moves;
}

int main() {
    cout << "n,time_milliseconds,expected_moves,actual_moves\n";
    
    for (int n = 15; n <= 1000; n++) {
        auto start = high_resolution_clock::now();
        unsigned long long moves = hanoiRecursive(n, 'A', 'C', 'B');
        auto stop = high_resolution_clock::now();
        
        auto duration = duration_cast<milliseconds>(stop - start);
        unsigned long long expected = (1ULL << n) - 1; // movements expected (theorically): 2^n - 1
        
        cout << n << "," << duration.count() << "," 
             << expected << "," << moves << "\n";
    }

    return 0;
}