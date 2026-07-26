#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <random>

using namespace std;

typedef unsigned long long ull;
typedef __int128 lll;

ull mul(ull a, ull b, ull mod) {
    return (ull)((lll)a * b % mod);
}

ull power(ull base, ull exp, ull mod) {
    base %= mod;
    ull res = 1;
    while (exp > 0) {
        if (exp & 1) res = mul(res, base, mod);
        base = mul(base, base, mod);
        exp >>= 1;
    }
    return res;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    for (ull p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) continue;
        ull x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

mt19937_64 rng(0x9e3779b9);

ull pollard(ull n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    if (n % 5 == 0) return 5;
    ull x = rng() % (n - 2) + 2;
    ull y = x;
    ull c = rng() % (n - 1) + 1;
    ull d = 1;
    while (d == 1) {
        x = (mul(x, x, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        d = __gcd(x > y ? x - y : y - x, n);
    }
    return d == n ? pollard(n) : d;
}

void factorize(ull n, map<ull, int>& factors) {
    if (n == 1) return;
    if (isPrime(n)) {
        factors[n]++;
        return;
    }
    ull d = pollard(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ull c;
    while (cin >> c && c != 0) {
        ull n = 4 * c - 3;
        map<ull, int> factors;
        factorize(n, factors);
        ull ans = 1;
        for (auto& p : factors) {
            ans *= (p.second + 1);
        }
        cout << c << " " << ans << "\n";
    }
    return 0;
}
