#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

/* ---------- NTT for a single modulus ---------- */
struct NTTMod {
    int mod, g;                 // modulus and primitive root
    vector<int> rev;
    vector<int> roots;

    NTTMod(int m, int primitive) : mod(m), g(primitive) {}

    int add(int a, int b) const {
        int s = a + b;
        if (s >= mod) s -= mod;
        return s;
    }
    int sub(int a, int b) const {
        int s = a - b;
        if (s < 0) s += mod;
        return s;
    }
    int mul(int a, int b) const {
        return int( (int64)a * b % mod );
    }
    int power(int a, long long e) const {
        int r = 1;
        while (e) {
            if (e & 1) r = mul(r, a);
            a = mul(a, a);
            e >>= 1;
        }
        return r;
    }

    void ensure_rev(int n) {
        if ((int)rev.size() == n) return;
        rev.assign(n, 0);
        int L = __builtin_ctz(n);
        for (int i = 0; i < n; ++i)
            rev[i] = (rev[i>>1]>>1) | ((i&1) << (L-1));
    }

    void ntt(vector<int> & a, bool invert) {
        int n = (int)a.size();
        ensure_rev(n);
        for (int i = 0; i < n; ++i)
            if (i < rev[i]) swap(a[i], a[rev[i]]);

        for (int len = 2, step = 1; len <= n; len <<= 1, ++step) {
            int wlen = power(g, (mod - 1) / len);
            if (invert) wlen = power(wlen, mod - 2);
            for (int i = 0; i < n; i += len) {
                int w = 1;
                for (int j = 0; j < len/2; ++j) {
                    int u = a[i+j];
                    int v = mul(a[i+j+len/2], w);
                    a[i+j] = add(u, v);
                    a[i+j+len/2] = sub(u, v);
                    w = mul(w, wlen);
                }
            }
        }
        if (invert) {
            int n_inv = power(n, mod - 2);
            for (int & x : a) x = mul(x, n_inv);
        }
    }

    vector<int> convolution(const vector<int> & a, const vector<int> & b) {
        int n1 = (int)a.size(), n2 = (int)b.size();
        if (!n1 || !n2) return {};
        int n = 1;
        while (n < n1 + n2 - 1) n <<= 1;
        vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        fa.resize(n); fb.resize(n);
        ntt(fa, false);
        ntt(fb, false);
        for (int i = 0; i < n; ++i) fa[i] = mul(fa[i], fb[i]);
        ntt(fa, true);
        fa.resize(n1 + n2 - 1);
        return fa;
    }
};

/* ---------- convolution modulo arbitrary M using CRT ---------- */
static const int MOD1 = 998244353;   // 2^23 * 7 * 17 + 1
static const int MOD2 = 1004535809; // 2^21 * 479 + 1
static const int G1 = 3;
static const int G2 = 3;

static NTTMod ntt1(MOD1, G1);
static NTTMod ntt2(MOD2, G2);

/* modular inverse of MOD1 modulo MOD2 (pre‑computed) */
static const int64 INV_MOD1_MOD2 = [](){
    long long a = MOD1, m = MOD2;
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m;
    if (u < 0) u += m;
    return u;               // MOD1 * u ≡ 1 (mod MOD2)
}();

/* convolution of two vectors modulo arbitrary MOD (≤ 1e7) */
static vector<int64> multiply_mod(const vector<int64> & a,
                                  const vector<int64> & b,
                                  int64 MOD) {
    if (a.empty() || b.empty()) return {};

    // convert to int vectors for each NTT modulus
    vector<int> a1(a.size()), b1(b.size());
    vector<int> a2(a.size()), b2(b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        int64 v = a[i] % MOD1; if (v < 0) v += MOD1;
        a1[i] = (int)v;
        v = a[i] % MOD2; if (v < 0) v += MOD2;
        a2[i] = (int)v;
    }
    for (size_t i = 0; i < b.size(); ++i) {
        int64 v = b[i] % MOD1; if (v < 0) v += MOD1;
        b1[i] = (int)v;
        v = b[i] % MOD2; if (v < 0) v += MOD2;
        b2[i] = (int)v;
    }

    vector<int> c1 = ntt1.convolution(a1, b1);
    vector<int> c2 = ntt2.convolution(a2, b2);

    size_t sz = c1.size();
    vector<int64> res(sz);
    for (size_t i = 0; i < sz; ++i) {
        int64 r1 = c1[i];
        int64 r2 = c2[i];
        // CRT reconstruction
        int64 t = ( (r2 - r1) % MOD2 + MOD2 ) % MOD2;
        t = (t * INV_MOD1_MOD2) % MOD2;
        i128 x = (i128)r1 + (i128)MOD1 * t;   // 0 ≤ x < MOD1*MOD2
        res[i] = (int64)(x % MOD);
    }
    return res;
}

/* ---------- helpers for Bostan–Mori ---------- */
static vector<int64> poly_even(const vector<int64> & p) {
    vector<int64> r;
    for (size_t i = 0; i < p.size(); i += 2) r.push_back(p[i]);
    return r;
}
static vector<int64> poly_odd(const vector<int64> & p) {
    vector<int64> r;
    for (size_t i = 1; i < p.size(); i += 2) r.push_back(p[i]);
    return r;
}

/* ---------- main solving routine ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long Mll;
    int K;
    long long N;
    while (cin >> Mll >> K >> N) {
        int64 MOD = Mll;
        if (MOD == 1) {               // everything is 0
            // still need to consume the two lines
            for (int i = 0; i < K; ++i) { long long x; cin >> x; }
            for (int i = 0; i < K; ++i) { long long x; cin >> x; }
            cout << 0 << '\n';
            continue;
        }

        vector<int64> a(K);
        for (int i = 0; i < K; ++i) {
            long long x; cin >> x;
            a[i] = (x % MOD + MOD) % MOD;
        }
        vector<int64> c(K + 1);               // 1‑based
        for (int i = 1; i <= K; ++i) {
            long long x; cin >> x;
            c[i] = (x % MOD + MOD) % MOD;
        }

        if (N <= K) {
            cout << a[N - 1] % MOD << '\n';
            continue;
        }

        /* characteristic polynomial Q(x) = 1 - c1 x - ... - cK x^K */
        vector<int64> Q(K + 1);
        Q[0] = 1 % MOD;
        for (int i = 1; i <= K; ++i) {
            Q[i] = (MOD - c[i]) % MOD;   // 1 - ci*x^i
        }

        /* P = ( Σ a_i x^i ) * Q  (mod x^K) */
        vector<int64> P = multiply_mod(a, Q, MOD);
        if ((int)P.size() > K) P.resize(K);
        else P.resize(K, 0);   // ensure size K

        long long n = N - 1;   // zero based index
        while (n > 0) {
            // Qneg(x) = Q(-x)
            vector<int64> Qneg = Q;
            for (size_t i = 1; i < Qneg.size(); i += 2)
                Qneg[i] = (MOD - Qneg[i]) % MOD;

            vector<int64> S = multiply_mod(P, Qneg, MOD);
            vector<int64> T = multiply_mod(Q, Qneg, MOD);

            if (n & 1LL) P = poly_odd(S);
            else        P = poly_even(S);
            Q = poly_even(T);
            n >>= 1;
        }
        int64 answer = P.empty() ? 0 : (P[0] % MOD);
        cout << answer << '\n';
    }
    return 0;
}
