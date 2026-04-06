#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ── Back substitution ─────────────────────────────────────────────────────────
// Takes an upper triangular augmented matrix [U|b] and solves for x.
// Also counts the number of multiplications/divisions performed.
vector<double> backSubstitution(vector<vector<double>> U, int n, int& ops) {
    vector<double> x(n);
    ops = 0;

    for (int i = n - 1; i >= 0; i--) {
        x[i] = U[i][n];

        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
            ops++;   // multiplication
        }

        x[i] /= U[i][i];
        ops++;       // division
    }

    return x;
}

// ── Print augmented matrix ────────────────────────────────────────────────────
void printMatrix(vector<vector<double>> U, int n) {
    cout << "  Augmented matrix [U|b]:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "    [";
        for (int j = 0; j < n; j++)
            cout << setw(6) << fixed << setprecision(2) << U[i][j];
        cout << "  |" << setw(7) << fixed << setprecision(2) << U[i][n] << " ]" << endl;
    }
}

// ── Print step-by-step back substitution ─────────────────────────────────────
void solveVerbose(vector<vector<double>> U, int n) {
    vector<double> x(n);

    cout << "  Step-by-step:" << endl;
    for (int i = n - 1; i >= 0; i--) {
        x[i] = U[i][n];
        cout << "    Row " << i << ": x[" << i << "] = " << U[i][n];

        for (int j = i + 1; j < n; j++) {
            cout << " - (" << fixed << setprecision(2) << U[i][j]
                 << " * " << x[j] << ")";
            x[i] -= U[i][j] * x[j];
        }

        cout << " / " << U[i][i] << " = ";
        x[i] /= U[i][i];
        cout << x[i] << endl;
    }
}

// ── Run one full example ──────────────────────────────────────────────────────
void runExample(int num, int n, vector<vector<double>> U, string expected) {
    cout << "============================================================" << endl;
    cout << "Example " << num << " — " << n << "x" << n << " system" << endl;
    cout << "============================================================" << endl;

    printMatrix(U, n);
    cout << endl;

    solveVerbose(U, n);
    cout << endl;

    int ops;
    vector<double> x = backSubstitution(U, n, ops);

    cout << "  Solution:" << endl;
    for (int i = 0; i < n; i++)
        cout << "    x[" << i << "] = " << fixed << setprecision(6) << x[i] << endl;

    cout << endl;
    cout << "  Expected          : " << expected << endl;
    cout << "  n                 : " << n << endl;
    cout << "  Actual op count   : " << ops << endl;
    cout << "  Formula n(n+1)/2  : " << n * (n + 1) / 2 << endl;
    cout << "  Running time      : O(n^2)" << endl;
    cout << endl;
}

int main() {

    // ── Example 1: 2x2 ───────────────────────────────────────────────────────
    //  3x0 + 2x1 = 8
    //        4x1 = 8
    //  Solution: x1=2, x0=4/3
    runExample(1, 2,
        {{3, 2, 8},
         {0, 4, 8}},
        "x[0]=1.333333  x[1]=2.000000");

    // ── Example 2: 3x3 ───────────────────────────────────────────────────────
    //  2x0 +  x1 -  x2 = 8
    //         4x1 + x2 = 2
    //               3x2 = -6
    //  Solution: x2=-2, x1=1, x0=3
    runExample(2, 3,
        {{2,  1, -1,  8},
         {0,  4,  1,  2},
         {0,  0,  3, -6}},
        "x[0]=3.000000  x[1]=1.000000  x[2]=-2.000000");

    // ── Example 3: 4x4 ───────────────────────────────────────────────────────
    //  2x0 + 3x1 -  x2 + 4x3 = 10
    //        5x1 + 2x2 -  x3 =  7
    //              4x2 + 3x3 = 14
    //                    6x3 = 12
    //  Solution: x3=2, x2=1, x1=1, x0=0
    runExample(3, 4,
        {{2, 3, -1, 4, 10},
         {0, 5,  2,-1,  7},
         {0, 0,  4, 3, 14},
         {0, 0,  0, 6, 12}},
        "x[0]=0.000000  x[1]=1.000000  x[2]=1.000000  x[3]=2.000000");

    // ── Complexity summary ────────────────────────────────────────────────────
    cout << "============================================================" << endl;
    cout << "Running time analysis" << endl;
    cout << "============================================================" << endl;
    cout << "  For each row i (from n-1 down to 0):" << endl;
    cout << "    - (n-1-i) multiplications in the inner loop" << endl;
    cout << "    - 1 division by the diagonal element" << endl;
    cout << endl;
    cout << "  Total ops = sum_{i=0}^{n-1} (n-i)" << endl;
    cout << "            = n + (n-1) + (n-2) + ... + 1" << endl;
    cout << "            = n(n+1)/2" << endl;
    cout << endl;
    cout << "  n=2  ->  " << 2*3/2 << " ops" << endl;
    cout << "  n=3  ->  " << 3*4/2 << " ops" << endl;
    cout << "  n=4  ->  " << 4*5/2 << " ops" << endl;
    cout << endl;
    cout << "  => Running time is O(n^2)" << endl;

    return 0;
}
