#include <iostream>
#include <unordered_map>

int fib(int n, std::unordered_map<int, int>& memo) {
    // Check if already computed
    if (memo.find(n) != memo.end())
        return memo[n];

    int result;

    // Base cases
    if (n == 1 || n == 2)
        result = 1;
    else
        // Pass memo to recursive calls (bug fixed)
        result = fib(n - 1, memo) + fib(n - 2, memo);

    memo[n] = result; // Store result for both base and recursive cases (bug fixed)
    return result;
}


// A test to the debuged function
int main() {
    std::unordered_map<int, int> memo;

    int n = 10;
    std::cout << "fib(" << n << ") = " << fib(n, memo) << std::endl;

    return 0;
}