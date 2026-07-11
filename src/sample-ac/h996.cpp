#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>

using namespace std;

const long long MOD = 1000000007LL;
const int MAXN = 200000;

long long modpow(long long a, long long e, long long mod) {
    long long res = 1;
    while (e) {
        if (e & 1) res = res * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}

void ntt(vector<int>& a, bool invert, int mod, int root) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = (int)modpow(root, (mod - 1) / len, mod);
        if (invert) wlen = (int)modpow(wlen, mod - 2, mod);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j];
                int v = (int)((long long)a[i + j + len / 2] * w % mod);
                a[i + j] = u + v < mod ? u + v : u + v - mod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)((long long)w * wlen % mod);
            }
        }
    }
    if (invert) {
        int n_inv = (int)modpow(n, mod - 2, mod);
        for (int& x : a) x = (int)((long long)x * n_inv % mod);
    }
}

vector<int> convolution_mod(const vector<int>& a, const vector<int>& b, int mod, int root) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size() - 1) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false, mod, root);
    ntt(fb, false, mod, root);
    for (int i = 0; i < n; i++) {
        fa[i] = (int)((long long)fa[i] * fb[i] % mod);
    }
    ntt(fa, true, mod, root);
    fa.resize(a.size() + b.size() - 1);
    return fa;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute factorials and inverse factorials up to MAXN
    vector<long long> fact(MAXN + 1), invfact(MAXN + 1);
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN] = modpow(fact[MAXN], MOD - 2, MOD);
    for (int i = MAXN; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;

    // Constants for t=3 convolution (three NTT-friendly primes)
    const int mod1 = 998244353, root1 = 3;
    const int mod2 = 1004535809, root2 = 3;
    const int mod3 = 469762049, root3 = 3;
    long long inv_m1_mod_m2 = modpow(mod1 % mod2, mod2 - 2, mod2);
    long long inv_m1m2_mod_m3 = modpow(( (long long)mod1 * mod2 ) % mod3, mod3 - 2, mod3);
    long long m1m2_mod_MOD = ( (long long)mod1 * mod2 ) % MOD;

    int n, m, t;
    while (cin >> n >> m >> t) {
        vector<long long> ans(m);
        if (t == 1) {
            for (int x = 1; x <= m; x++) {
                ans[x - 1] = modpow(x, n, MOD);
            }
        } else if (t == 2) {
            for (int x = 1; x <= m; x++) {
                ans[x - 1] = fact[n + x - 1] * invfact[n] % MOD * invfact[x - 1] % MOD;
            }
        } else if (t == 3) {
            // Compute Stirling numbers S(n, k) for k = 0..n
            vector<long long> A(n + 1), B(n + 1);
            for (int i = 0; i <= n; i++) {
                long long pow_i = (i == 0 ? 0 : modpow(i, n, MOD));
                A[i] = pow_i * invfact[i] % MOD;
                B[i] = (i % 2 == 0 ? 1 : MOD - 1) * invfact[i] % MOD;
            }

            // Convert to three moduli
            vector<int> A1(n + 1), B1(n + 1), A2(n + 1), B2(n + 1), A3(n + 1), B3(n + 1);
            for (int i = 0; i <= n; i++) {
                A1[i] = (int)(A[i] % mod1);
                B1[i] = (int)(B[i] % mod1);
                A2[i] = (int)(A[i] % mod2);
                B2[i] = (int)(B[i] % mod2);
                A3[i] = (int)(A[i] % mod3);
                B3[i] = (int)(B[i] % mod3);
            }

            vector<int> c1 = convolution_mod(A1, B1, mod1, root1);
            vector<int> c2 = convolution_mod(A2, B2, mod2, root2);
            vector<int> c3 = convolution_mod(A3, B3, mod3, root3);

            vector<long long> S(n + 1);
            for (int k = 0; k <= n; k++) {
                long long r1 = c1[k];
                long long r2 = c2[k];
                long long r3 = c3[k];
                long long x1 = r1;
                long long x2 = ( (r2 - x1) % mod2 + mod2 ) % mod2 * inv_m1_mod_m2 % mod2;
                long long x3 = ( (r3 - x1 - (long long)mod1 * x2) % mod3 + mod3 ) % mod3 * inv_m1m2_mod_m3 % mod3;
                long long val = x1;
                val = (val + (long long)mod1 * x2) % MOD;
                val = (val + m1m2_mod_MOD * x3) % MOD;
                S[k] = val;
            }

            vector<long long> pref(n + 1);
            pref[0] = 0;
            for (int k = 1; k <= n; k++) {
                pref[k] = (pref[k - 1] + S[k]) % MOD;
            }
            for (int x = 1; x <= m; x++) {
                ans[x - 1] = (x <= n) ? pref[x] : pref[n];
            }
        }

        for (int i = 0; i < m; i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
