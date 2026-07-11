#include <iostream>

using namespace std;

unsigned long long mul(unsigned long long a, unsigned long long b, unsigned long long mod) {
    return (unsigned long long)((__int128)a * b % mod);
}

unsigned long long pow_mod(unsigned long long a, unsigned long long b, unsigned long long mod) {
    unsigned long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    while (cin >> T) {
        while (T--) {
            unsigned long long N, M, L;
            cin >> N >> M >> L;
            unsigned long long mod = N + 1;
            unsigned long long inv2 = (N + 2) / 2;
            unsigned long long inv2_M = pow_mod(inv2, M, mod);
            unsigned long long ans = mul(L, inv2_M, mod);
            if (ans == 0) ans = mod;
            cout << ans << "\n";
        }
    }
    return 0;
}
