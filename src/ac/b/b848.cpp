#include <iostream>
#include <cstdint>

const long long MOD = 1000007LL;

struct Matrix {
    long long a[2][2];
    Matrix(bool ident = false) {
        a[0][0] = a[1][1] = ident ? 1 : 0;
        a[0][1] = a[1][0] = 0;
    }
};

Matrix multiply(const Matrix& x, const Matrix& y) {
    Matrix r;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            long long sum = 0;
            for (int k = 0; k < 2; ++k) {
                sum += x.a[i][k] * y.a[k][j];
                if (sum >= (1LL << 60)) sum %= MOD;   // avoid overflow
            }
            r.a[i][j] = sum % MOD;
        }
    return r;
}

Matrix power(Matrix base, long long exp) {
    Matrix res(true);               // identity
    while (exp > 0) {
        if (exp & 1LL) res = multiply(res, base);
        base = multiply(base, base);
        exp >>= 1LL;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    if (!(std::cin >> T)) return 0;
    while (T--) {
        long long N, M, K;
        std::cin >> N >> M >> K;

        long long male, female;
        if (K == 0) {
            male = N % MOD;
            female = M % MOD;
        } else if (N == M) {
            male = N % MOD;
            female = M % MOD;
        } else {
            long long a0 = N % MOD;
            long long a1;
            if (N > M) {
                a1 = ( (M % MOD) + (2LL * (N % MOD)) ) % MOD;
            } else { // M > N
                a1 = (3LL * (M % MOD)) % MOD;
            }

            if (K == 1) {
                male = a1;
                female = a0;
            } else {
                Matrix Tmat;
                Tmat.a[0][0] = 0; Tmat.a[0][1] = 1;
                Tmat.a[1][0] = 1; Tmat.a[1][1] = 2;
                Matrix P = power(Tmat, K - 1);
                long long a_k_minus_1 = (P.a[0][0] * a0 + P.a[0][1] * a1) % MOD;
                long long a_k        = (P.a[1][0] * a0 + P.a[1][1] * a1) % MOD;
                male   = a_k;
                female = a_k_minus_1;
            }
        }
        std::cout << male << ' ' << female << '\n';
    }
    return 0;
}
