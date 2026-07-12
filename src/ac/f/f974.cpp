#include <iostream>

using namespace std;

const long long MOD = 1000000007;

long long pow_mod(long long base, unsigned long long exp) {
    long long res = 1;
    base %= MOD;
    if (base < 0) base += MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long x;
    unsigned long long n;
    while (cin >> x >> n) {
        if (x == 0 && n == 0) break;
        if (x == 1) {
            cout << (n + 1) % MOD << "\n";
        } else {
            long long xn1 = pow_mod(x, n + 1);
            long long inv = pow_mod(x - 1, MOD - 2);
            cout << (xn1 - 1 + MOD) % MOD * inv % MOD << "\n";
        }
    }
    return 0;
}
