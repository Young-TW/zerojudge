#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long MOD = 1e8 + 7;

long long modpow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long modinv(long long a, long long mod) {
    return modpow(a, mod - 2, mod);
}

long long comb(long long n, long long m) {
    if (m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1;
    if (m > n - m) m = n - m;

    long long numerator = 1;
    for (long long i = n - m + 1; i <= n; ++i) {
        numerator = numerator * i % MOD;
    }

    long long denominator = 1;
    for (long long i = 1; i <= m; ++i) {
        denominator = denominator * i % MOD;
    }

    return numerator * modinv(denominator, MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n, m;
        cin >> n >> m;
        cout << comb(n, m) << '\n';
    }

    return 0;
}
