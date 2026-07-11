#include <iostream>

using namespace std;

const long long MOD = 998244353;

long long power(long long base, unsigned long long exp) {
    long long res = 1;
    base %= MOD;
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
    int T;
    while (cin >> T) {
        for (int i = 0; i < T; ++i) {
            unsigned long long N;
            cin >> N;
            long long ans;
            if (N == 1) ans = 1;
            else if (N == 2) ans = 2;
            else if (N == 3) ans = 3;
            else if (N == 4) ans = 4;
            else {
                if (N % 3 == 0) {
                    ans = power(3, N / 3);
                } else if (N % 3 == 1) {
                    ans = (4 * power(3, (N - 4) / 3)) % MOD;
                } else {
                    ans = (2 * power(3, (N - 2) / 3)) % MOD;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
