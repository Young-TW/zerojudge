#include <iostream>

using namespace std;

const long long MOD = 1000000007;

long long fast_pow(long long base, long long exp) {
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
    
    long long n;
    while (cin >> n) {
        if (n < 2) {
            cout << 0 << "\n";
            continue;
        }
        long long ans = (n % MOD) * ((n - 1) % MOD) % MOD;
        ans = (ans * fast_pow(2, n - 2)) % MOD;
        cout << ans << "\n";
    }
    
    return 0;
}
