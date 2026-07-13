#include <iostream>

using namespace std;

const int MOD = 10007;

void mat_mul(long long A[2][2], long long B[2][2], long long C[2][2]) {
    long long temp[2][2];
    temp[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % MOD;
    temp[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % MOD;
    temp[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % MOD;
    temp[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % MOD;
    C[0][0] = temp[0][0];
    C[0][1] = temp[0][1];
    C[1][0] = temp[1][0];
    C[1][1] = temp[1][1];
}

long long fib(long long n) {
    if (n == 0) return 0;
    long long res[2][2] = {{1, 0}, {0, 1}};
    long long base[2][2] = {{1, 1}, {1, 0}};
    while (n > 0) {
        if (n % 2 == 1) {
            mat_mul(res, base, res);
        }
        mat_mul(base, base, base);
        n /= 2;
    }
    return res[0][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    while (cin >> n) {
        cout << fib(n) << "\n";
    }
    return 0;
}
