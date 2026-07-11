#include <iostream>

using namespace std;

const long long MOD = 1000000007LL;

long long modpow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            long long p, k;
            if (!(cin >> p >> k)) break;
            long long ans;
            if (p % MOD == 1) {
                ans = k % MOD;
            } else {
                long long pk = modpow(p, k, MOD);
                long long inv = modpow((p - 1) % MOD, MOD - 2, MOD);
                ans = (pk - 1 + MOD) % MOD;
                ans = (ans * inv) % MOD;
            }
            cout << "Case " << i << ": " << ans << "\n";
        }
    }
    return 0;
}
