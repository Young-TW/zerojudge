#include <iostream>

using namespace std;

long long modpow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    while (cin >> n) {
        if (n <= 0) {
            cout << 0 << "\n";
        } else {
            cout << modpow(2, n - 1, 1234567) << "\n";
        }
    }
    return 0;
}
