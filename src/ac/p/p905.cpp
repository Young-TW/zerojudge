#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using i128 = __int128_t;

// ---------- modular arithmetic ----------
static inline int64 mul_mod(int64 a, int64 b, int64 mod) {
    return (int64)((i128)a * b % mod);
}
static inline int64 pow_mod(int64 a, int64 d, int64 mod) {
    int64 r = 1;
    while (d) {
        if (d & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return r;
}

// ---------- Miller‑Rabin (deterministic for 64‑bit) ----------
bool isPrime(int64 n) {
    if (n < 2) return false;
    static const int64 small_primes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (int64 p : small_primes) {
        if (n % p == 0) return n == p;
    }
    int64 d = n - 1, s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }

    // bases sufficient for 64‑bit integers
    const int64 bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (int64 a : bases) {
        if (a % n == 0) continue;
        int64 x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

// ---------- next prime ----------
int64 nextPrime(int64 n) {
    int64 x = n + 1;
    while (!isPrime(x)) ++x;
    return x;
}

// ---------- next perfect square ----------
int64 nextSquare(int64 n) {
    long double d = sqrt((long double)n);
    int64 s = (int64)d;
    while (s * s <= n) ++s;
    return s * s;
}

// ---------- next perfect cube ----------
int64 cubePower(int64 x) { return x * x * x; }

int64 nextCube(int64 n) {
    // binary search for floor(cuberoot(n))
    int64 lo = 0, hi = 1;
    while (cubePower(hi) <= n) hi <<= 1;
    while (lo + 1 < hi) {
        int64 mid = lo + (hi - lo) / 2;
        if (cubePower(mid) <= n) lo = mid;
        else hi = mid;
    }
    // lo = floor(cuberoot(n))
    ++lo; // first integer > cuberoot
    return cubePower(lo);
}

// ---------- main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 N;
    while (cin >> N) {
        int64 P = nextPrime(N);
        int64 S = nextSquare(N);
        int64 C = nextCube(N);
        cout << P << ' ' << S << ' ' << C << '\n';
    }
    return 0;
}
