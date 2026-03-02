#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Helper function to make a valid move between two pegs
void moveDisk(vector<int>& pegA, vector<int>& pegB) {
    if (pegA.empty()) {
        pegA.push_back(pegB.back());
        pegB.pop_back();
    } else if (pegB.empty()) {
        pegB.push_back(pegA.back());
        pegA.pop_back();
    } else if (pegA.back() < pegB.back()) {
        // Top of pegA is smaller, so move A to B
        pegB.push_back(pegA.back());
        pegA.pop_back();
    } else {
        // Top of pegB is smaller, so move B to A
        pegA.push_back(pegB.back());
        pegB.pop_back();
    }
}

void hanoiIterative(int n) {
    vector<int> source, target, auxiliary;
    
    // Initialize the source peg with n disks (with the largest one at bottom, and the smallest one at top)
    for (int i = n; i >= 1; i--) {
        source.push_back(i);
    }

    long long total_moves = pow(2, n) - 1;
    
    // Determine the logical roles of the pegs based on whether n is even or odd
    vector<int>* dest = &target;
    vector<int>* aux = &auxiliary;
    if (n % 2 == 0) {
        dest = &auxiliary;
        aux = &target;
    }

    // The iterative cycle repeats every 3 moves
    for (long long i = 1; i <= total_moves; i++) {
        if (i % 3 == 1) {
            moveDisk(source, *dest);
        } else if (i % 3 == 2) {
            moveDisk(source, *aux);
        } else if (i % 3 == 0) {
            moveDisk(*aux, *dest);
        }
    }
}

int main() {
    cout << "n,time_milliseconds\n";
    
    // We test with n from 15 to 25
    for (int n = 15; n <= 25; n++) {
        auto start = high_resolution_clock::now();
        
        hanoiIterative(n);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        
        cout << n << "," << duration.count() << "\n";
    }

    return 0;
}