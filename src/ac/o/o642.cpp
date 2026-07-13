#include <iostream>

using namespace std;

const int MOD = 998244353;
const int MAXN = 400005;

long long fact[MAXN];
long long inv2_pow[MAXN];

long long modpow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    long long inv2 = modpow(2, MOD - 2, MOD);
    inv2_pow[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        inv2_pow[i] = (inv2_pow[i - 1] * inv2) % MOD;
    }

    long long inv3 = modpow(3, MOD - 2, MOD);

    int n;
    while (cin >> n) {
        long long ans = n;
        ans = (ans * n) % MOD;
        long long term = (4LL * n * n % MOD - 1 + MOD) % MOD;
        ans = (ans * term) % MOD;
        ans = (ans * fact[2 * n - 2]) % MOD;
        ans = (ans * inv3) % MOD;
        ans = (ans * inv2_pow[n - 1]) % MOD;
        cout << ans << "\n";
    }

    return 0;
}
