#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G = 3;                     // primitive root

int addmod(int a, int b) { int s = a + b; if (s >= MOD) s -= MOD; return s; }
int submod(int a, int b) { int s = a - b; if (s < 0) s += MOD; return s; }
int mulmod(long long a, long long b) { return int(a * b % MOD); }
int powmod(int a, long long e) {
    int r = 1;
    while (e) {
        if (e & 1) r = mulmod(r, a);
        a = mulmod(a, a);
        e >>= 1;
    }
    return r;
}
int invmod(int a) { return powmod(a, MOD - 2); }

void ntt(vector<int> & a, bool invert) {
    int n = (int)a.size();
    static vector<int> rev;
    static vector<int> roots{0,1};
    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n);
        rev.assign(n,0);
        for (int i=0;i<n;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    }
    if ((int)roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1<<k) < n) {
            int z = powmod(G, (MOD-1)>>(k+1));
            for (int i=1<<(k-1); i<(1<<k); ++i) {
                roots[2*i]=roots[i];
                roots[2*i+1]=mulmod(roots[i],z);
            }
            ++k;
        }
    }
    for (int i=0;i<n;i++) if (i<rev[i]) swap(a[i],a[rev[i]]);
    for (int len=1; len<n; len<<=1) {
        for (int i=0;i<n;i+=2*len) {
            for (int j=0;j<len;j++) {
                int u = a[i+j];
                int v = mulmod(a[i+j+len], roots[len+j]);
                a[i+j] = addmod(u,v);
                a[i+j+len] = submod(u,v);
            }
        }
    }
    if (invert) {
        reverse(a.begin()+1, a.end());
        int inv_n = invmod(n);
        for (int & x : a) x = mulmod(x, inv_n);
    }
}

vector<int> multiply(const vector<int> & a, const vector<int> & b, int need) {
    int n1 = (int)a.size(), n2 = (int)b.size();
    int n = 1;
    while (n < n1 + n2 - 1) n <<= 1;
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);
    ntt(fa,false); ntt(fb,false);
    for (int i=0;i<n;i++) fa[i] = mulmod(fa[i], fb[i]);
    ntt(fa,true);
    if ((int)fa.size() > need) fa.resize(need);
    else if ((int)fa.size() < need) fa.resize(need,0);
    return fa;
}

// inverse of series a modulo x^n, a[0] != 0
vector<int> invert_series(const vector<int> & a, int n) {
    vector<int> res(1, invmod(a[0]));
    int cur = 1;
    while (cur < n) {
        cur <<= 1;
        vector<int> a_cut(min((int)a.size(), cur));
        for (int i=0;i<(int)a_cut.size();i++) a_cut[i]=a[i];
        vector<int> tmp = multiply(multiply(res, res, cur), a_cut, cur);
        res.resize(cur);
        for (int i=0;i<cur;i++) {
            res[i] = submod(addmod(res[i], res[i]), tmp[i]);
        }
    }
    res.resize(n);
    return res;
}

// derivative
vector<int> derivative(const vector<int> & a) {
    int n = (int)a.size();
    if (n==1) return vector<int>{0};
    vector<int> res(n-1);
    for (int i=1;i<n;i++) res[i-1] = mulmod(a[i], i);
    return res;
}

// integral (assumes inv of 1..n pre‑computed)
vector<int> integral(const vector<int> & a, const vector<int> & inv) {
    int n = (int)a.size();
    vector<int> res(n+1,0);
    for (int i=0;i<n;i++) res[i+1] = mulmod(a[i], inv[i+1]);
    return res;
}

// logarithm, a[0]=1
vector<int> logarithm(const vector<int> & a, int need, const vector<int> & inv) {
    vector<int> der = derivative(a);
    vector<int> inva = invert_series(a, need);
    vector<int> q = multiply(der, inva, need-1);
    vector<int> res = integral(q, inv);
    res.resize(need);
    return res;
}

// exponentiation, g[0]=0
vector<int> exponent(const vector<int> & g, int need, const vector<int> & inv) {
    vector<int> res(1,1);
    int cur = 1;
    while (cur < need) {
        cur <<= 1;
        vector<int> res_cut = res;
        res_cut.resize(cur);
        vector<int> g_cut(g.begin(), g.begin() + min((int)g.size(), cur));
        vector<int> log_res = logarithm(res_cut, cur, inv);
        // delta = g_cut - log_res
        vector<int> delta(cur);
        for (int i=0;i<cur;i++) {
            int gv = i < (int)g_cut.size() ? g_cut[i] : 0;
            delta[i] = submod(gv, log_res[i]);
        }
        delta[0] = addmod(delta[0], 1); // 1 + (g - log)
        vector<int> new_res = multiply(res, delta, cur);
        res.swap(new_res);
    }
    res.resize(need);
    return res;
}

// compute n % MOD from decimal string
int mod_string(const string & s) {
    long long r = 0;
    for (char c : s) {
        r = (r * 10 + (c - '0')) % MOD;
    }
    return (int)r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string n_str;
    int m, k;
    while (cin >> n_str >> m >> k) {
        vector<int> a(m);
        for (int i = 0; i < m; ++i) cin >> a[i];

        int n_mod = mod_string(n_str);

        // pre‑compute inverses of 1..k+1
        vector<int> inv(k + 2);
        inv[1] = 1;
        for (int i = 2; i <= k + 1; ++i)
            inv[i] = mulmod(MOD - MOD / i, inv[MOD % i]);

        // build F(x) = 1 + Σ x^{a_i}
        vector<int> F(k + 1, 0);
        F[0] = 1;
        for (int v : a) if (v <= k) {
            F[v] = addmod(F[v], 1);
        }

        // log(F)
        vector<int> L = logarithm(F, k + 1, inv);
        for (int i = 0; i <= k; ++i)
            L[i] = mulmod(L[i], n_mod);

        // exp(L)
        vector<int> R = exponent(L, k + 1, inv);

        unsigned long long ans = 0;
        for (int i = 0; i <= k; ++i) ans ^= (unsigned long long)R[i];
        cout << ans << '\n';
    }
    return 0;
}
