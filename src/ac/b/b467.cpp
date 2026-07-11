#include <iostream>

using namespace std;

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
    long long n, m, k, x;
    while (cin >> n >> m >> k >> x) {
        long long p = power(10, k, n);
        long long ans = (x + (p * (m % n)) % n) % n;
        cout << ans << "\n";
    }
    return 0;
}
