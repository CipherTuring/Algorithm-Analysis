#include <iostream>
#include <vector>
using namespace std;

// ── Heapify down from index i in a heap of size n ────────────────────────────
// Assumes both subtrees of i are already valid max-heaps.
// Pushes i down until the max-heap property is restored.
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;          // assume current node is the largest
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    // If a child is larger, swap and keep pushing down
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// ── Build max-heap from an arbitrary array (Floyd's algorithm) ────────────────
// Start from the last internal node and heapify down to the root.
// Running time: O(n)
void buildHeap(vector<int>& arr) {
    int n = arr.size();

    // Last internal node is at index n/2 - 1
    // Leaf nodes are already trivial heaps, so we skip them
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

// ── Print array ───────────────────────────────────────────────────────────────
void printArray(vector<int>& arr, string label) {
    cout << label;
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// ── Print heap as a tree (level by level) ────────────────────────────────────
void printTree(vector<int>& arr) {
    int n = arr.size();
    int level = 0;
    int count = 1;   // nodes per level: 1, 2, 4, 8, ...
    int i = 0;

    cout << "  Heap tree (level by level):" << endl;
    while (i < n) {
        cout << "    Level " << level << ": ";
        for (int k = 0; k < count && i < n; k++, i++)
            cout << arr[i] << " ";
        cout << endl;
        level++;
        count *= 2;
    }
}

// ── Verify max-heap property ──────────────────────────────────────────────────
bool isMaxHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n / 2; i++) {
        int left  = 2 * i + 1;
        int right = 2 * i + 2;
        if (left  < n && arr[left]  > arr[i]) return false;
        if (right < n && arr[right] > arr[i]) return false;
    }
    return true;
}

// ── Run one example ───────────────────────────────────────────────────────────
void runExample(int num, vector<int> arr) {
    cout << "============================================================" << endl;
    cout << "Example " << num << endl;
    cout << "============================================================" << endl;

    printArray(arr, "  Input array : ");

    buildHeap(arr);

    printArray(arr, "  After buildHeap: ");
    printTree(arr);
    cout << "  Max element at root : " << arr[0] << endl;
    cout << "  Valid max-heap      : " << (isMaxHeap(arr) ? "YES" : "NO") << endl;
    cout << endl;
}

int main() {

    // Example 1: small array
    runExample(1, {3, 1, 6, 5, 2, 4});

    // Example 2: already sorted ascending (worst case for naive approach)
    runExample(2, {1, 2, 3, 4, 5, 6, 7});

    // Example 3: reverse sorted
    runExample(3, {9, 8, 7, 6, 5, 4, 3, 2, 1});

    // Complexity note
    cout << "============================================================" << endl;
    cout << "Running time analysis" << endl;
    cout << "============================================================" << endl;
    cout << "  Naive approach: call heapify on every node => O(n log n)" << endl;
    cout << "  Floyd's algorithm: start from last internal node => O(n)" << endl;
    cout << "    - Nodes at height h: at most ceil(n / 2^(h+1))" << endl;
    cout << "    - heapify cost at height h: O(h)" << endl;
    cout << "    - Total: sum over h of ceil(n/2^(h+1)) * h = O(n)" << endl;

    return 0;
}
