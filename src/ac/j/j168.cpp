#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
const long long MOD = 1000000007;

long long fact[MAXN];
long long invfact[MAXN];
long long pow2[MAXN];

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invfact[MAXN - 1] = power(fact[MAXN - 1], MOD - 2, MOD);
    for (int i = MAXN - 2; i >= 0; i--) {
        invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;
    }
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    
    int t;
    if (cin >> t) {
        while (t--) {
            int n, m;
            cin >> n >> m;
            int a = n - 1;
            int b = m - 1;
            if (a > b) {
                swap(a, b);
            }
            long long ans = 0;
            for (int k = 0; k <= a; k++) {
                long long ca = fact[a] * invfact[k] % MOD * invfact[a - k] % MOD;
                long long cb = fact[b] * invfact[k] % MOD * invfact[b - k] % MOD;
                long long term = ca * cb % MOD * pow2[k] % MOD;
                ans = (ans + term) % MOD;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
