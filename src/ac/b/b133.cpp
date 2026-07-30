#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const unsigned long long MOD = 1ULL << 31;   // 2^31

    long long k, N;
    while (cin >> k >> N) {
        unsigned long long ans = 0;
        unsigned long long power = 1;           // k^0  (mod MOD)
        unsigned long long n = static_cast<unsigned long long>(N);

        while (n) {
            if (n & 1ULL) {
                ans += power;
                if (ans >= MOD) ans -= MOD;     // ans %= MOD, faster
            }
            power *= static_cast<unsigned long long>(k);
            if (power >= MOD) power %= MOD;
            n >>= 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
