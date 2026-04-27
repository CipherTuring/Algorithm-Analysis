#include <iostream>
#include <vector>
#include <algorithm>

// Returns the maximum value that can be put in a knapsack of given capacity
int knapsack(int capacity, std::vector<int>& weights, std::vector<int>& values, int n) {
    // Build DP table of size (n+1) x (capacity+1)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // Option 1: Don't take item i
            dp[i][w] = dp[i - 1][w];

            // Option 2: Take item i (only if it fits)
            if (weights[i - 1] <= w) {
                int withItem = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                dp[i][w] = std::max(dp[i][w], withItem);
            }
        }
    }

    return dp[n][capacity];
}

// This traces back the DP table to find which items were selected
std::vector<int> getSelectedItems(int capacity, std::vector<int>& weights,
                                   std::vector<int>& values, int n,
                                   std::vector<std::vector<int>>& dp) {
    std::vector<int> selected;
    int w = capacity;

    for (int i = n; i >= 1; i--) {
        // If value changed from previous row, item i was included
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i);
            w -= weights[i - 1];
        }
    }

    return selected;
}

int main() {
    std::vector<int> values  = {60, 100, 120};
    std::vector<int> weights = {10,  20,  30};
    int capacity = 50;
    int n = values.size();

    // Build DP table
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i - 1][w];
            if (weights[i - 1] <= w) {
                int withItem = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                dp[i][w] = std::max(dp[i][w], withItem);
            }
        }
    }

    // Print DP table
    std::cout << "DP Table:\n";
    std::cout << "Item\\Cap";
    for (int w = 0; w <= capacity; w += 10)
        std::cout << "\t" << w;
    std::cout << "\n";
    for (int i = 0; i <= n; i++) {
        std::cout << "  " << i << "\t";
        for (int w = 0; w <= capacity; w += 10)
            std::cout << "\t" << dp[i][w];
        std::cout << "\n";
    }

    // Get results
    int maxValue = dp[n][capacity];
    std::vector<int> selected = getSelectedItems(capacity, weights, values, n, dp);

    std::cout << "\n--- Results ---\n";
    std::cout << "Maximum Value : " << maxValue << "\n";
    std::cout << "Items Selected: ";
    for (int idx : selected)
        std::cout << "Item " << idx << " (weight=" << weights[idx-1]
                  << ", value=" << values[idx-1] << ")  ";
    std::cout << "\n";

    return 0;
}