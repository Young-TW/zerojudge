#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

// ---------- Euler totient ----------
int64 euler_phi(int64 n) {
    int64 res = n;
    for (int64 p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

// ---------- modular power ----------
int64 mod_pow(int64 a, int64 e, int64 mod) {
    int64 r = 1 % mod;
    a %= mod;
    while (e) {
        if (e & 1) r = (i128)r * a % mod;
        a = (i128)a * a % mod;
        e >>= 1;
    }
    return r;
}

// ---------- test whether a^e >= limit ----------
bool power_ge_limit(int64 a, int64 e, int64 limit) {
    if (limit <= 1) return true;
    i128 cur = 1;
    i128 base = a;
    while (e) {
        if (e & 1) {
            cur *= base;
            if (cur >= limit) return true;
        }
        e >>= 1;
        if (e) {
            base *= base;
            if (base >= limit) base = limit;   // cap, we only need “≥ limit”
        }
    }
    return false;
}

// ---------- global data ----------
vector<int64> a;          // 1‑based
vector<int64> mods;       // totient chain, mods[0] = m

// ---------- recursive solver ----------
pair<int64,bool> solve(int l, int r, int idx) {
    // returns (value modulo mods[idx] , big flag)
    if (idx == (int)mods.size() - 1) {          // modulus = 1
        return {0, true};
    }
    int64 mod = mods[idx];
    if (l == r) {
        int64 v = a[l] % mod;
        bool big = (a[l] >= mod);
        return {v, big};
    }
    if (a[l] == 1) {
        int64 v = 1 % mod;
        bool big = (1 >= mod);
        return {v, big};
    }
    // exponent from the right part
    auto expPair = solve(l + 1, r, idx + 1);
    int64 phi = mods[idx + 1];
    int64 e = expPair.first + (expPair.second ? phi : 0);
    int64 val = mod_pow(a[l] % mod, e, mod);

    bool big;
    if (a[l] >= mod) big = true;
    else big = power_ge_limit(a[l], e, mod);

    return {val, big};
}

// ---------- main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int64 m;
    while (cin >> n >> m) {
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        // build totient chain
        mods.clear();
        mods.push_back(m);
        while (mods.back() != 1) {
            mods.push_back(euler_phi(mods.back()));
        }

        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            auto ans = solve(l, r, 0);
            cout << ans.first << '\n';
        }
    }
    return 0;
}
