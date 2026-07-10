#include <iostream>
using namespace std;

const int P = 10007;

long long power(long long base, long long exp, long long mod) {
    long long res = 1 % mod;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Lucas theorem: C(n, m) mod p, p prime
long long lucas(long long n, long long m, long long p) {
    if (m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1 % p;
    long long res = 1 % p;
    while (n > 0 || m > 0) {
        long long ni = n % p;
        long long mi = m % p;
        if (mi > ni) return 0;
        // C(ni, mi) mod p, ni < p so compute directly
        long long num = 1, den = 1;
        for (long long i = 0; i < mi; i++) {
            num = num * ((ni - i) % p) % p;
            den = den * ((i + 1) % p) % p;
        }
        res = res * num % p * power(den, p - 2, p) % p;
        n /= p;
        m /= p;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, k, n, m;
    while (cin >> a >> b >> k >> n >> m) {
        long long ans = lucas(k, n, P);
        ans = ans * power(a, n, P) % P;
        ans = ans * power(b, m, P) % P;
        cout << ans << "\n";
    }
    return 0;
}
