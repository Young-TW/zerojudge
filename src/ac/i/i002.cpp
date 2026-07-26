#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int64 MOD = 998244353;
const int64 G   = 3;                 // primitive root

int64 mod_pow(int64 a, int64 e) {
    int64 r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}
int64 mod_inv(int64 a) { return mod_pow(a, MOD - 2); }

/* ---------- NTT ---------- */
void ntt(vector<int64> & a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int64 wlen = mod_pow(G, (MOD - 1) / len);
        if (invert) wlen = mod_inv(wlen);
        for (int i = 0; i < n; i += len) {
            int64 w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int64 u = a[i + j];
                int64 v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }

    if (invert) {
        int64 n_inv = mod_inv(n);
        for (int64 & x : a) x = x * n_inv % MOD;
    }
}

vector<int64> multiply(const vector<int64> & a, const vector<int64> & b) {
    if (a.empty() || b.empty()) return {};
    int need = (int)a.size() + (int)b.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    vector<int64> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; ++i) fa[i] = fa[i] * fb[i] % MOD;
    ntt(fa, true);
    fa.resize(need);
    return fa;
}

/* ---------- helpers for Bostan–Mori ---------- */
vector<int64> even_coeff(const vector<int64> & v) {
    vector<int64> r;
    for (size_t i = 0; i < v.size(); i += 2) r.push_back(v[i]);
    return r;
}
vector<int64> odd_coeff(const vector<int64> & v) {
    vector<int64> r;
    for (size_t i = 1; i < v.size(); i += 2) r.push_back(v[i]);
    return r;
}

/* ---------- Bostan–Mori ---------- */
int64 bostan_mori(vector<int64> P, vector<int64> Q, long long k) {
    // invariant: answer = coeff_{x^k} (P/Q)
    while (k > 0) {
        // Q(-x)
        vector<int64> Qneg = Q;
        for (size_t i = 1; i < Qneg.size(); i += 2) {
            Qneg[i] = (MOD - Qneg[i]) % MOD;
        }
        vector<int64> S = multiply(P, Qneg);
        vector<int64> T = multiply(Q, Qneg);
        if (k & 1) {
            P = odd_coeff(S);
        } else {
            P = even_coeff(S);
        }
        Q = even_coeff(T);
        k >>= 1;
        // keep degrees bounded (degree of Q never exceeds original n)
        if ((int)P.size() > (int)Q.size()) P.resize(Q.size());
        // optional truncation to original n (not strictly necessary)
    }
    // Q[0] == 1, but keep generic formula
    return P[0] * mod_inv(Q[0]) % MOD;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    while (cin >> n >> k) {
        vector<int64> f(n);
        for (int i = 0; i < n; ++i) {
            cin >> f[i];
            f[i] %= MOD;
        }
        vector<int64> a(n + 1);          // 1‑based for convenience
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            a[i] %= MOD;
        }

        if (k <= n) {
            cout << f[(int)k - 1] % MOD << '\n';
            continue;
        }

        // build Q(x) = 1 - a1 x - a2 x^2 - ... - an x^n
        vector<int64> Q(n + 1);
        Q[0] = 1;
        for (int i = 1; i <= n; ++i) {
            Q[i] = (MOD - a[i]) % MOD;
        }

        // P = (f * Q) mod x^n
        vector<int64> tmp = multiply(f, Q);   // size ≤ 2n
        vector<int64> P(n);
        for (int i = 0; i < n; ++i) P[i] = tmp[i] % MOD;

        int64 ans = bostan_mori(P, Q, k - 1);
        cout << ans << '\n';
    }
    return 0;
}
