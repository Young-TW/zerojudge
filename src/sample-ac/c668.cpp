#include <iostream>

using namespace std;
using u64 = unsigned long long;

u64 mulmod(u64 a, u64 b, u64 m) {
#ifdef __SIZEOF_INT128__
    return (u64)((__uint128_t)a * b % m);
#else
    u64 res = 0;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            res += a;
            if (res >= m) res -= m;
        }
        a <<= 1;
        if (a >= m) a -= m;
        b >>= 1;
    }
    return res;
#endif
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
    
    u64 d = n - 1;
    int r = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    
    for (u64 a : {2ULL, 7ULL, 61ULL}) {
        if (a >= n) continue;
        u64 x = 1;
        u64 base = a;
        u64 exp = d;
        while (exp > 0) {
            if (exp & 1) x = mulmod(x, base, n);
            base = mulmod(base, base, n);
            exp >>= 1;
        }
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    u64 min_val, max_val;
    while (cin >> T >> min_val >> max_val) {
        while (T--) {
            u64 n;
            cin >> n;
            u64 p = n + 1;
            if (p <= 2) {
                cout << 2 << "\n";
                continue;
            }
            if (p % 2 == 0) p++;
            while (!isPrime(p)) {
                p += 2;
            }
            cout << p << "\n";
        }
    }
    return 0;
}
