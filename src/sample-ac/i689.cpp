#pragma GCC optimize("O3")
#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1000000007;

struct Matrix {
    int n;
    vector<long long> a;
    Matrix(int _n) : n(_n), a((size_t)_n * _n) {}
    long long& operator()(int i, int j) {
        return a[(size_t)i * n + j];
    }
    long long operator()(int i, int j) const {
        return a[(size_t)i * n + j];
    }
};

Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.n;
    Matrix C(n);
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            long long aik = A(i, k);
            if (aik == 0) continue;
            for (int j = 0; j < n; ++j) {
                C(i, j) = (C(i, j) + aik * B(k, j)) % MOD;
            }
        }
    }
    return C;
}

Matrix power(Matrix base, long long exp) {
    int n = base.n;
    Matrix res(n);
    for (int i = 0; i < n; ++i) res(i, i) = 1;
    while (exp > 0) {
        if (exp & 1) res = multiply(res, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        Matrix A(n);
        for (int i = 0; i < n; ++i) {
            int m;
            cin >> m;
            for (int j = 0; j < m; ++j) {
                int v;
                cin >> v;
                A(i, v - 1) = 1;
            }
        }
        long long q, t;
        cin >> q >> t;
        Matrix At = power(A, t);
        while (q--) {
            int a, b;
            cin >> a >> b;
            cout << At(a - 1, b - 1) << "\n";
        }
    }
    return 0;
}
