#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
using int64 = long long;

/* multiply two polynomials (degree < n) modulo the characteristic polynomial
   x^n = a1 x^{n-1} + ... + an
   a[0] = a1 , ..., a[n-1] = an
   result is stored in a vector of size n
*/
vector<int> combine(const vector<int>& A, const vector<int>& B,
                    const vector<int>& a) {
    int n = (int)a.size();
    vector<int64> tmp(2 * n - 1, 0);
    for (int i = 0; i < n; ++i) if (A[i])
        for (int j = 0; j < n; ++j) if (B[j]) {
            tmp[i + j] += (int64)A[i] * B[j];
            if (tmp[i + j] >= (1LL << 62)) tmp[i + j] %= MOD; // avoid overflow
        }
    for (int i = 0; i < (int)tmp.size(); ++i) tmp[i] %= MOD;

    // reduction of degrees >= n
    for (int d = 2 * n - 2; d >= n; --d) {
        int64 coeff = tmp[d] % MOD;
        if (coeff == 0) continue;
        for (int j = 1; j <= n; ++j) {
            tmp[d - j] += coeff * a[j - 1];
            if (tmp[d - j] >= (1LL << 62)) tmp[d - j] %= MOD;
        }
        // tmp[d] can be discarded
    }

    vector<int> res(n);
    for (int i = 0; i < n; ++i) res[i] = (int)(tmp[i] % MOD);
    return res;
}

/* compute the k‑th term (0‑based index) of the recurrence */
int kth_term(long long k, const vector<int>& init, const vector<int>& a) {
    int n = (int)a.size();
    if (k < n) return init[(int)k];

    // binary exponentiation of x
    vector<int> poly(n, 0);   // represents x^0
    poly[0] = 1;
    vector<int> base(n, 0);   // represents x
    if (n > 1) base[1] = 1;
    else base[0] = a[0]; // when n==1, x ≡ a1 (mod P)

    long long exp = k;
    while (exp) {
        if (exp & 1LL) poly = combine(poly, base, a);
        base = combine(base, base, a);
        exp >>= 1LL;
    }

    int64 ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += (int64)poly[i] * init[i];
        if (ans >= (1LL << 62)) ans %= MOD;
    }
    return (int)(ans % MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    while (cin >> n >> k) {
        vector<int> f(n), a(n);
        for (int i = 0; i < n; ++i) {
            int x; cin >> x; f[i] = x % MOD;
        }
        for (int i = 0; i < n; ++i) {
            int x; cin >> x; a[i] = x % MOD;
        }
        // convert to 0‑based indexing: f[0] = f1, …
        int ans = kth_term(k - 1, f, a);   // problem uses 1‑based k
        cout << ans << '\n';
    }
    return 0;
}
