#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

int n;

// ── Print a matrix ────────────────────────────────────────────────────────────
void printMatrix(vector<vector<double>>& mat, string label) {
    cout << "  " << label << endl;
    for (int i = 0; i < n; i++) {
        cout << "    [";
        for (int j = 0; j < n; j++)
            cout << setw(8) << fixed << setprecision(3) << mat[i][j];
        cout << " ]" << endl;
    }
    cout << endl;
}

// ── Print a vector ────────────────────────────────────────────────────────────
void printVector(vector<double>& v, string label) {
    cout << "  " << label << "[ ";
    for (double x : v)
        cout << fixed << setprecision(6) << x << "  ";
    cout << "]" << endl;
}

// ── LU Decomposition (based on Gaussian Elimination) ─────────────────────────
//
// Decomposes A into L and U such that A = L * U
//
//   U  : upper triangular  (built just like forward elimination)
//   L  : lower triangular  (stores the multipliers used during elimination)
//
// No pivoting here to keep it readable — same idea as basic Gaussian elimination
//
void luDecompose(vector<vector<double>> A,
                 vector<vector<double>>& L,
                 vector<vector<double>>& U)
{
    // Start U as a copy of A, L as identity
    U = A;
    L.assign(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        L[i][i] = 1.0;   // diagonal of L is always 1

    for (int col = 0; col < n; col++) {
        for (int row = col + 1; row < n; row++) {
            double factor = U[row][col] / U[col][col];   // same multiplier as Gaussian elimination
            L[row][col] = factor;                         // store it in L

            for (int k = col; k < n; k++)
                U[row][k] -= factor * U[col][k];          // eliminate (same row op as forward elimination)
        }
    }
}

// ── Forward substitution  Ly = b ─────────────────────────────────────────────
// L is lower triangular with 1s on diagonal
vector<double> forwardSub(vector<vector<double>>& L, vector<double>& b) {
    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++)
            y[i] -= L[i][j] * y[j];
        // no division needed since L[i][i] = 1
    }
    return y;
}

// ── Back substitution  Ux = y ─────────────────────────────────────────────────
vector<double> backSub(vector<vector<double>>& U, vector<double>& y) {
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }
    return x;
}

// ── Compute residual  max|Ax - b| ─────────────────────────────────────────────
double residual(vector<vector<double>>& A, vector<double>& x, vector<double>& b) {
    double maxErr = 0;
    for (int i = 0; i < n; i++) {
        double ax = 0;
        for (int j = 0; j < n; j++) ax += A[i][j] * x[j];
        maxErr = max(maxErr, abs(ax - b[i]));
    }
    return maxErr;
}

// ── Run one full example ───────────────────────────────────────────────────────
void runExample(int num, vector<vector<double>> A, vector<double> b, string expected) {
    cout << "============================================================" << endl;
    cout << "Example " << num << " — " << n << "x" << n << " system" << endl;
    cout << "============================================================" << endl;

    printMatrix(A, "Matrix A:");

    // Step 1: LU decomposition
    vector<vector<double>> L, U;
    luDecompose(A, L, U);

    printMatrix(L, "L (lower triangular — stores multipliers):");
    printMatrix(U, "U (upper triangular — result of forward elimination):");

    // Step 2: solve Ly = b
    vector<double> y = forwardSub(L, b);
    printVector(y, "y  (from Ly = b): ");

    // Step 3: solve Ux = y
    vector<double> x = backSub(U, y);
    printVector(x, "x  (from Ux = y): ");

    cout << "  Expected          : " << expected << endl;
    cout << "  Residual |Ax - b| : " << residual(A, x, b) << endl;
    cout << endl;
}

int main() {

    // ── Example 1: 2x2 ───────────────────────────────────────────────────────
    //  4x0 + 3x1 = 10
    //  6x0 + 3x1 = 12
    //  Solution: x0=1, x1=2
    n = 2;
    runExample(1,
        {{4, 3},
         {6, 3}},
        {10, 12},
        "x[0]=1.000000  x[1]=2.000000");

    // ── Example 2: 3x3 ───────────────────────────────────────────────────────
    //  2x0 +  x1 -  x2 = 8
    // -3x0 -  x1 + 2x2 = -11
    // -2x0 +  x1 + 2x2 = -3
    //  Solution: x0=2, x1=3, x2=-1
    n = 3;
    runExample(2,
        {{ 2,  1, -1},
         {-3, -1,  2},
         {-2,  1,  2}},
        {8, -11, -3},
        "x[0]=2.000000  x[1]=3.000000  x[2]=-1.000000");

    // ── Example 3: 4x4 ───────────────────────────────────────────────────────
    //  Solution: x0=x1=x2=x3=1
    n = 4;
    runExample(3,
        {{4, 3, 2, 1},
         {3, 4, 3, 2},
         {2, 3, 4, 3},
         {1, 2, 3, 4}},
        {10, 12, 12, 10},
        "x[0]=1.000000  x[1]=1.000000  x[2]=1.000000  x[3]=1.000000");

    return 0;
}
