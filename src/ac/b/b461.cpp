#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;

/*------------------------------------------------------------*/
/* basic number theory                                         */
static u64 ugcd(u64 a, u64 b) {
    while (b) {
        u64 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/* extended Euclid, returns (g, x, y) with ax + by = g = gcd(a,b) */
static i128 egcd(i128 a, i128 b, i128 &x, i128 &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    i128 x1, y1;
    i128 g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

/* modular inverse, a and m must be coprime */
static u64 modInv(u64 a, u64 m) {
    i128 x, y;
    egcd((i128)a, (i128)m, x, y);
    i128 r = x % (i128)m;
    if (r < 0) r += m;
    return (u64)r;
}

/*------------------------------------------------------------*/
/* fast doubling Fibonacci modulo m                           */
static pair<u64,u64> fib_pair(u64 n, u64 mod) {
    if (n == 0) return {0ULL, 1ULL % mod};
    auto pr = fib_pair(n >> 1, mod);
    u64 a = pr.first;          // F_k
    u64 b = pr.second;         // F_{k+1}

    u64 two_b = (b << 1) % mod;
    u64 two_b_minus_a = (two_b + mod - a) % mod;

    u64 c = (u64)((u128)a * two_b_minus_a % mod);          // F_{2k}
    u64 d = (u64)(((u128)a * a + (u128)b * b) % mod);      // F_{2k+1}

    if (n & 1ULL) {
        u64 e = (c + d) % mod;
        return {d, e};
    } else {
        return {c, d};
    }
}

/*------------------------------------------------------------*/
/* solve for a prime power p^K                                 */
static vector<u64> solve_prime_power(int p, int K, u64 target) {
    u64 mod = (u64)p;
    u64 period = (p == 2) ? 3ULL : 20ULL;
    vector<u64> sols;

    for (u64 n = 0; n < period; ++n) {
        if (fib_pair(n, mod).first == target % mod)
            sols.push_back(n);
    }

    for (int e = 2; e <= K; ++e) {
        u64 prev_mod = mod;
        u64 prev_period = period;
        mod *= (u64)p;
        u64 factor = (p == 2) ? 2ULL : 5ULL;
        period *= factor;

        vector<u64> nxt;
        u64 target_mod = target % mod;

        for (u64 base : sols) {
            for (u64 t = 0; t < factor; ++t) {
                u64 n = base + t * prev_period;
                if (fib_pair(n, mod).first == target_mod)
                    nxt.push_back(n % period);
            }
        }
        sort(nxt.begin(), nxt.end());
        nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
        sols.swap(nxt);
        if (sols.empty()) break;
    }
    return sols;
}

/*------------------------------------------------------------*/
/* CRT for possibly non‑coprime moduli                         */
static bool crt(u64 a, u64 m1, u64 b, u64 m2, u64 &res, u64 &lcm) {
    u64 g = ugcd(m1, m2);
    if ((a % g) != (b % g)) return false;

    u64 m1_g = m1 / g;
    u64 m2_g = m2 / g;
    u64 diff = (b >= a) ? (b - a) : (b + m2 - a);
    u64 diff_div = diff / g;                     // now < m2_g

    u64 inv = modInv(m1_g % m2_g, m2_g);
    u64 t = (u64)((u128)diff_div * inv % m2_g);

    u128 n = (u128)a + (u128)m1 * t;
    lcm = (u128)m1_g * m2;                       // = lcm(m1,m2)
    res = (u64)(n % lcm);
    return true;
}

/*------------------------------------------------------------*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, T;
    if (!(cin >> K >> T)) return 0;

    /* periods for 2^K and 5^K */
    u64 per2, per5;
    if (K == 1) per2 = 3;
    else if (K == 2) per2 = 6;
    else per2 = 3ULL << (K - 1);                 // 3·2^{K-1}

    per5 = 20ULL;
    for (int i = 2; i <= K; ++i) per5 *= 5ULL;   // 20·5^{K-1}

    u64 per10 = per2 / ugcd(per2, per5) * per5; // lcm

    const string NO = "You've slept foolish!";

    for (int q = 0; q < T; ++q) {
        string s;
        cin >> s;
        u64 x = 0;
        for (char c : s) x = x * 10ULL + (c - '0');

        /* residues modulo prime powers */
        u64 mod2 = 1ULL << K;                    // 2^K
        u64 mod5 = 1ULL;
        for (int i = 0; i < K; ++i) mod5 *= 5ULL; // 5^K

        vector<u64> S2 = solve_prime_power(2, K, x % mod2);
        vector<u64> S5 = solve_prime_power(5, K, x % mod5);

        if (S2.empty() || S5.empty()) {
            cout << NO << '\n';
            continue;
        }

        bool found = false;
        u64 best = 0;    // placeholder

        for (u64 a : S2) {
            for (u64 b : S5) {
                u64 n, l;
                if (crt(a, per2, b, per5, n, l)) {
                    if (!found || n < best) {
                        best = n;
                        found = true;
                    }
                }
            }
        }

        if (!found) cout << NO << '\n';
        else        cout << (best + 1ULL) << '\n';
    }
    return 0;
}
