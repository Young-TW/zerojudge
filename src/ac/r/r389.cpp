#include <iostream>

using namespace std;

const long long MOD = 1000000007LL;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long x;
            cin >> x;
            long long ans = 1;
            if (x == 1) {
                ans = 1;
            } else if (x == 2) {
                ans = 2;
            } else if (x == 3) {
                ans = 3;
            } else {
                long long q = x / 3;
                long long r = x % 3;
                if (r == 0) {
                    ans = power(3, q);
                } else if (r == 1) {
                    ans = (power(3, q - 1) * 4) % MOD;
                } else {
                    ans = (power(3, q) * 2) % MOD;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
