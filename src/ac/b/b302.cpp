#include <iostream>

using namespace std;

const long long MOD = 100000007;

struct Matrix {
    long long a, b, c, d;
};

Matrix multiply(const Matrix& x, const Matrix& y) {
    Matrix res;
    res.a = (x.a * y.a + x.b * y.c) % MOD;
    res.b = (x.a * y.b + x.b * y.d) % MOD;
    res.c = (x.c * y.a + x.d * y.c) % MOD;
    res.d = (x.c * y.b + x.d * y.d) % MOD;
    return res;
}

Matrix mat_pow(Matrix base, long long exp) {
    Matrix res = {1, 0, 0, 1};
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
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long N;
            cin >> N;
            if (N == 0 || N == 1) {
                cout << 1 << "\n";
            } else {
                Matrix base = {1, 1, 1, 0};
                Matrix res = mat_pow(base, N - 1);
                long long ans = (res.a + res.b) % MOD;
                cout << ans << "\n";
            }
        }
    }
    return 0;
}
