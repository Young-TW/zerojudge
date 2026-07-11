#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

Matrix multiply(const Matrix& a, const Matrix& b, int n) {
    Matrix c(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (a[i][k] == 0) continue;
            for (int j = 0; j < n; ++j) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % 10;
            }
        }
    }
    return c;
}

Matrix add(const Matrix& a, const Matrix& b, int n) {
    Matrix c(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = (a[i][j] + b[i][j]) % 10;
        }
    }
    return c;
}

Matrix solve(int k, const Matrix& A, int n) {
    if (k == 1) return A;
    
    vector<Matrix> power_A(21, Matrix(n, vector<int>(n, 0)));
    vector<Matrix> sum_A(21, Matrix(n, vector<int>(n, 0)));
    
    power_A[0] = A;
    sum_A[0] = A;
    
    int max_bit = 0;
    while ((1 << max_bit) <= k) {
        max_bit++;
    }
    
    for (int i = 1; i <= max_bit; ++i) {
        power_A[i] = multiply(power_A[i-1], power_A[i-1], n);
        sum_A[i] = add(sum_A[i-1], multiply(power_A[i-1], sum_A[i-1], n), n);
    }
    
    Matrix S(n, vector<int>(n, 0));
    Matrix P(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) P[i][i] = 1;
    
    for (int i = 0; i <= max_bit; ++i) {
        if ((k >> i) & 1) {
            S = add(S, multiply(P, sum_A[i], n), n);
            P = multiply(P, power_A[i], n);
        }
    }
    
    return S;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k && n) {
        Matrix A(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> A[i][j];
                A[i][j] %= 10;
            }
        }
        Matrix S = solve(k, A, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << S[i][j];
                if (j < n - 1) cout << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}
