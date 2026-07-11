#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_MOD = 100000000;
const int MAX_K = 18;

struct Matrix {
    long long mat[2][2];
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }
    Matrix operator*(const Matrix& other) const {
        Matrix res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % MAX_MOD;
                }
            }
        }
        return res;
    }
};

Matrix matrix_pow(Matrix base, long long exp) {
    Matrix res;
    res.mat[0][0] = res.mat[1][1] = 1;
    while (exp > 0) {
        if (exp & 1) {
            res = res * base;
        }
        base = base * base;
        exp >>= 1;
    }
    return res;
}

long long fib_mod(long long n, long long mod) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    Matrix m;
    m.mat[0][0] = m.mat[0][1] = m.mat[1][0] = 1;
    m.mat[1][1] = 0;
    Matrix res = matrix_pow(m, n - 1);
    return res.mat[0][0] % mod;
}

int find_min_n(long long x, int K, long long mod) {
    if (K == 1) {
        if (x == 0) return 0;
        if (x == 1) return 1;
        for (int n = 2; n <= 60; ++n) {
            if (fib_mod(n, mod) == x) {
                return n;
            }
        }
        return -1;
    }

    long long target = x;
    vector<long long> fibs;
    vector<int> indices;
    long long a = 0, b = 1;
    fibs.push_back(a);
    indices.push_back(0);
    if (a == target) return 0;
    for (int i = 1; i <= 3 * mod; ++i) {
        long long c = (a + b) % mod;
        a = b;
        b = c;
        fibs.push_back(a);
        indices.push_back(i);
        if (a == target) {
            return i;
        }
        if (i > mod && a == 0 && b == 1) {
            break;
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, T;
    cin >> K >> T;
    long long mod = 1;
    for (int i = 0; i < K; ++i) {
        mod *= 10;
    }

    while (T--) {
        string s;
        cin >> s;
        long long x = 0;
        for (char c : s) {
            x = (x * 10 + (c - '0')) % mod;
        }

        int n = find_min_n(x, K, mod);
        if (n == -1) {
            cout << "You've slept foolish!\n";
        } else {
            cout << n + 1 << '\n';
        }
    }

    return 0;
}
