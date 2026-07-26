#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <cstdint>

using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;

u64 mulmod(u64 a, u64 b, u64 m) {
    return (u64)((u128)a * b % m);
}

u64 powmod(u64 a, u64 e, u64 m) {
    u64 r = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return r;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1;
    int r = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) continue;
        u64 x = powmod(a, d, n);
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

mt19937_64 rng(123456789);

u64 pollard(u64 n) {
    if (n % 2 == 0) return 2;
    while (true) {
        u64 x = rng() % (n - 2) + 2;
        u64 y = x;
        u64 c = rng() % (n - 1) + 1;
        u64 d = 1;
        while (d == 1) {
            x = (mulmod(x, x, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            u64 diff = (x > y) ? (x - y) : (y - x);
            if (diff == 0) break;
            d = __gcd(diff, n);
        }
        if (d != n && d != 0) return d;
    }
}

void factorize(u64 n, vector<u64>& factors) {
    if (n == 1) return;
    if (isPrime(n)) {
        factors.push_back(n);
        return;
    }
    u64 d = pollard(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    u64 n;
    while (cin >> n) {
        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }
        vector<u64> factors;
        factorize(n, factors);
        sort(factors.begin(), factors.end());
        factors.erase(unique(factors.begin(), factors.end()), factors.end());
        
        u64 result = n;
        for (u64 p : factors) {
            result = result / p * (p - 1);
        }
        cout << result << '\n';
    }
    return 0;
}
