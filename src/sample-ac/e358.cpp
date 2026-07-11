#include <iostream>

using namespace std;

const long long MOD = 1000000007;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        if (N == 0) {
            cout << 0 << "\n";
            continue;
        }
        long long or_sum = 0;
        for (int i = 0; i < N; ++i) {
            long long x;
            cin >> x;
            or_sum |= x;
        }
        long long p = power(2, N - 1, MOD);
        long long ans = (or_sum % MOD) * p % MOD;
        cout << ans << "\n";
    }
    return 0;
}
