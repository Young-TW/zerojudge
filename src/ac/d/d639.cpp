#include <iostream>

using namespace std;

const int MOD = 10007;

struct Matrix {
    int m[3][3];
    Matrix() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] = 0;
            }
        }
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix res;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                res.m[i][j] = (res.m[i][j] + a.m[i][k] * b.m[k][j]) % MOD;
            }
        }
    }
    return res;
}

Matrix matrixPow(Matrix base, long long exp) {
    Matrix res;
    for (int i = 0; i < 3; ++i) {
        res.m[i][i] = 1;
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = multiply(res, base);
        }
        base = multiply(base, base);
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        if (n <= 3) {
            cout << 1 << "\n";
            continue;
        }
        
        Matrix base;
        base.m[0][0] = 1; base.m[0][1] = 1; base.m[0][2] = 1;
        base.m[1][0] = 1; base.m[1][1] = 0; base.m[1][2] = 0;
        base.m[2][0] = 0; base.m[2][1] = 1; base.m[2][2] = 0;
        
        Matrix res = matrixPow(base, n - 3);
        
        int ans = (res.m[0][0] + res.m[0][1] + res.m[0][2]) % MOD;
        cout << ans << "\n";
    }
    
    return 0;
}
