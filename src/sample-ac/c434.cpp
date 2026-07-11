#include <iostream>

using namespace std;

const long long MOD = 1000000007;

struct Matrix {
    long long m[3][3];
    Matrix() {
        for(int i=0; i<3; ++i)
            for(int j=0; j<3; ++j)
                m[i][j] = 0;
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c;
    for(int i=0; i<3; ++i) {
        for(int k=0; k<3; ++k) {
            if(a.m[i][k] == 0) continue;
            for(int j=0; j<3; ++j) {
                c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j]) % MOD;
            }
        }
    }
    return c;
}

Matrix mat_pow(Matrix a, long long p) {
    Matrix res;
    for(int i=0; i<3; ++i) res.m[i][i] = 1;
    while(p > 0) {
        if(p & 1) res = multiply(res, a);
        a = multiply(a, a);
        p >>= 1;
    }
    return res;
}

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while(exp > 0) {
        if(exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while(cin >> T) {
        while(T--) {
            long long n;
            if(!(cin >> n)) break;
            if(n <= 2) {
                cout << 0 << "\n";
                continue;
            }
            
            Matrix M;
            M.m[0][0] = 1; M.m[0][1] = 1; M.m[0][2] = 1;
            M.m[1][0] = 1; M.m[1][1] = 0; M.m[1][2] = 0;
            M.m[2][0] = 0; M.m[2][1] = 1; M.m[2][2] = 0;
            
            Matrix res = mat_pow(M, n - 2);
            
            long long A_n = (res.m[0][0] * 4 + res.m[0][1] * 2 + res.m[0][2] * 1) % MOD;
            
            long long pow2n = power(2, n);
            
            long long ans = (pow2n - A_n + MOD) % MOD;
            cout << ans << "\n";
        }
    }
    return 0;
}
