#include <iostream>
#include <string>
using namespace std;

typedef unsigned long long u64;
typedef __uint128_t u128;

// modular multiplication via __int128 to avoid overflow for 64-bit inputs
static inline u64 mulmod(u64 a, u64 b, u64 m) {
    return (u64)((u128)a * b % m);
}

// modular exponentiation
static inline u64 powmod(u64 a, u64 d, u64 m) {
    u64 r = 1 % m;
    a %= m;
    while (d) {
        if (d & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        d >>= 1;
    }
    return r;
}

// Miller-Rabin single witness test
// n is odd, n-1 = d * 2^s
static inline bool witness(u64 a, u64 d, u64 n, int s) {
    u64 x = powmod(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int i = 0; i < s - 1; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return false;
    }
    return true; // composite
}

// deterministic Miller-Rabin for n < 2^32 -> witnesses {2,7,61}
// (sufficient for n < 4,759,123,141; covers all x up to 2147483647)
static bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) {
            return n == p;
        }
    }
    // write n-1 = d * 2^s
    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (u64 a : {2ULL, 7ULL, 61ULL}) {
        if (a >= n) continue;
        if (witness(a, d, n, s)) return false;
    }
    return true;
}

int main() {
    // fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    // read all tokens
    u64 x;
    while (cin >> x) {
        cout << (isPrime(x) ? "\xe8\xb3\xaa\xe6\x95\xb8" : "\xe9\x9d\x9e\xe8\xb3\xaa\xe6\x95\xb8") << '\n';
    }
    return 0;
}
