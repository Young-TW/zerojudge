#include <iostream>

using namespace std;

const int MOD = 10007;
int fact[MOD];
int inv_fact[MOD];

int power(int base, int exp, int mod) {
    int res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MOD; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv_fact[MOD - 1] = power(fact[MOD - 1], MOD - 2, MOD);
    for (int i = MOD - 2; i >= 0; --i) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int n;
    while (cin >> n) {
        if (n >= 5004) {
            cout << 0 << "\n";
        } else {
            int ans = (C(2 * n, n) - C(2 * n, n + 1) + MOD) % MOD;
            cout << ans << "\n";
        }
    }
    return 0;
}
