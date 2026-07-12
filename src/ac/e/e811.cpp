#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MOD = 10000;

struct Matrix {
    long long m[3][3];
    Matrix() {
        memset(m, 0, sizeof(m));
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j]) % MOD;
            }
        }
    }
    return c;
}

Matrix power(Matrix base, long long exp) {
    Matrix res;
    for (int i = 0; i < 3; ++i) {
        res.m[i][i] = 1;
    }
    while (exp > 0) {
        if (exp & 1) {
            res = multiply(res, base);
        }
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long P, Q, R, A0, A1, N;
    while (cin >> P >> Q >> R >> A0 >> A1 >> N) {
        if (N == 0) {
            cout << setfill('0') << setw(4) << A0 % MOD << "\n";
            continue;
        }
        
        Matrix base;
        base.m[0][0] = P % MOD;
        base.m[0][1] = Q % MOD;
        base.m[0][2] = 1;
        base.m[1][0] = 1;
        base.m[1][1] = 0;
        base.m[1][2] = 0;
        base.m[2][0] = 0;
        base.m[2][1] = 0;
        base.m[2][2] = 1;
        
        Matrix res = power(base, N - 1);
        
        long long ans = (res.m[0][0] * (A1 % MOD) + res.m[0][1] * (A0 % MOD) + res.m[0][2] * (R % MOD)) % MOD;
        
        cout << setfill('0') << setw(4) << ans << "\n";
    }
    
    return 0;
}
