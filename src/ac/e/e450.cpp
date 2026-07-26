#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u128 = __uint128_t;

struct Matrix {
    u64 a, b, c, d;               // [[a,b],[c,d]]
};

static inline Matrix mul(const Matrix& x, const Matrix& y, u64 mod) {
    Matrix r;
    u128 t;
    t = (u128)x.a * y.a + (u128)x.b * y.c;
    r.a = (u64)(t % mod);
    t = (u128)x.a * y.b + (u128)x.b * y.d;
    r.b = (u64)(t % mod);
    t = (u128)x.c * y.a + (u128)x.d * y.c;
    r.c = (u64)(t % mod);
    t = (u128)x.c * y.b + (u128)x.d * y.d;
    r.d = (u64)(t % mod);
    return r;
}

static Matrix mat_pow(Matrix base, u64 exp, u64 mod) {
    Matrix res{1, 0, 0, 1};               // identity
    while (exp) {
        if (exp & 1) res = mul(res, base, mod);
        base = mul(base, base, mod);
        exp >>= 1;
    }
    return res;
}

/*  check whether M^k == I (mod mod)  */
static bool is_identity(u64 k, u64 mod) {
    Matrix M{1, 1, 1, 0};
    Matrix R = mat_pow(M, k, mod);
    return R.a == 1 && R.b == 0 && R.c == 0 && R.d == 1;
}

/*  smallest period for a prime p  */
static u64 pisano_prime(u64 p, const vector<int>& spf) {
    if (p == 2) return 3;
    if (p == 5) return 20;
    u64 N;
    u64 r = p % 10;
    if (r == 1 || r == 9) N = p - 1;
    else                 N = 2 * (p + 1);

    // factorise N
    vector<u64> fac;
    u64 tmp = N;
    while (tmp > 1) {
        int q = spf[tmp];
        fac.push_back(q);
        while (tmp % q == 0) tmp /= q;
    }

    u64 d = N;
    for (u64 q : fac) {
        while (d % q == 0 && is_identity(d / q, p))
            d /= q;
    }
    return d;
}

/*  greatest common divisor  */
static u64 my_gcd(u64 a, u64 b) {
    while (b) {
        u64 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/*  least common multiple  */
static u64 my_lcm(u64 a, u64 b) {
    if (a == 0 || b == 0) return 0;
    return a / my_gcd(a, b) * b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;

    int MAX = max(n, 2 * (n + 1));
    vector<int> spf(MAX + 1, 0);
    vector<int> primes;
    spf[0] = spf[1] = 1;
    for (int i = 2; i <= MAX; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > MAX) break;
            spf[v] = p;
            if (p == spf[i]) break;
        }
    }

    // period for each prime <= n
    vector<u64> primePeriod(n + 1, 0);
    for (int p : primes) {
        if (p > n) break;
        primePeriod[p] = pisano_prime(p, spf);
    }

    vector<u64> period(n + 1, 0);
    period[1] = 1;
    for (int x = 2; x <= n; ++x) {
        u64 ans = 1;
        int y = x;
        while (y > 1) {
            int p = spf[y];
            int cnt = 0;
            while (y % p == 0) {
                y /= p;
                ++cnt;
            }
            u64 cur = primePeriod[p];          // π(p)
            for (int i = 1; i < cnt; ++i) cur *= (u64)p;   // *p^{cnt-1}
            ans = my_lcm(ans, cur);
        }
        period[x] = ans;
    }

    for (int i = 1; i <= n; ++i) {
        cout << period[i] << '\n';
    }
    return 0;
}
