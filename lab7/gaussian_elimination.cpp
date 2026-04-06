#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n = 3;

    // Augmented matrix [A|b] for the system:
    //  2x  +  y  -  z = 8
    // -3x  -  y  + 2z = -11
    // -2x  +  y  + 2z = -3
    // Solution: x=2, y=3, z=-1
    vector<vector<double>> mat = {
        { 2,  1, -1,   8},
        {-3, -1,  2, -11},
        {-2,  1,  2,  -3}
    };

    // ── Forward Elimination ───────────────────────────────────────────────────
    for (int col = 0; col < n; col++) {

        // Find the row with the biggest value in this column (partial pivoting)
        int maxRow = col;
        for (int row = col + 1; row < n; row++) {
            if (abs(mat[row][col]) > abs(mat[maxRow][col]))
                maxRow = row;
        }

        // Swap that row with the current row
        swap(mat[col], mat[maxRow]);

        // Eliminate all rows below
        for (int row = col + 1; row < n; row++) {
            double factor = mat[row][col] / mat[col][col];
            for (int k = col; k <= n; k++)
                mat[row][k] -= factor * mat[col][k];
        }
    }

    // ── Back Substitution ─────────────────────────────────────────────────────
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = mat[i][n];
        for (int j = i + 1; j < n; j++)
            x[i] -= mat[i][j] * x[j];
        x[i] /= mat[i][i];
    }

    // ── Print solution ────────────────────────────────────────────────────────
    cout << "Solution:" << endl;
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << x[i] << endl;

    return 0;
}
