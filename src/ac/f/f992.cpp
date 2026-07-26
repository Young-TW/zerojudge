#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000003LL;

int n, K, Q;
vector<long long> a;               // 1‑based
vector<long long> S1, S2, S3;      // prefix sums of i, i^2, i^3 (mod MOD)

struct SegTree {
    struct Node {
        long long sum = 0;
        long long lazy[4] = {0,0,0,0};   // coefficients a0..a3
    };
    vector<Node> t;
    SegTree(int n = 0) { init(n); }

    void init(int n) { t.assign(4 * n + 4, Node()); }

    // helpers for prefix sums on interval [L,R] (1‑based)
    inline long long rangeSum(const vector<long long>& pref, int L, int R) const {
        long long res = pref[R] - pref[L-1];
        if (res < 0) res += MOD;
        return res;
    }

    // apply polynomial (a0..a3) to node idx covering [L,R]
    void apply(int idx, int L, int R,
               long long a0, long long a1, long long a2, long long a3) {
        long long len = R - L + 1;
        long long add = (a0 % MOD) * (len % MOD) % MOD;
        add = (add + a1 % MOD * rangeSum(S1, L, R)) % MOD;
        add = (add + a2 % MOD * rangeSum(S2, L, R)) % MOD;
        add = (add + a3 % MOD * rangeSum(S3, L, R)) % MOD;
        t[idx].sum += add;
        if (t[idx].sum >= MOD) t[idx].sum -= MOD;

        t[idx].lazy[0] = (t[idx].lazy[0] + a0) % MOD;
        t[idx].lazy[1] = (t[idx].lazy[1] + a1) % MOD;
        t[idx].lazy[2] = (t[idx].lazy[2] + a2) % MOD;
        t[idx].lazy[3] = (t[idx].lazy[3] + a3) % MOD;
    }

    void push(int idx, int L, int R) {
        long long a0 = t[idx].lazy[0];
        long long a1 = t[idx].lazy[1];
        long long a2 = t[idx].lazy[2];
        long long a3 = t[idx].lazy[3];
        if (a0==0 && a1==0 && a2==0 && a3==0) return;
        int mid = (L + R) >> 1;
        apply(idx<<1, L, mid, a0, a1, a2, a3);
        apply(idx<<1|1, mid+1, R, a0, a1, a2, a3);
        for (int i=0;i<4;i++) t[idx].lazy[i]=0;
    }

    void build(int idx, int L, int R) {
        if (L == R) {
            t[idx].sum = a[L] % MOD;
            return;
        }
        int mid = (L + R) >> 1;
        build(idx<<1, L, mid);
        build(idx<<1|1, mid+1, R);
        t[idx].sum = t[idx<<1].sum + t[idx<<1|1].sum;
        if (t[idx].sum >= MOD) t[idx].sum -= MOD;
    }

    // range update with polynomial coeffs
    void update(int idx, int L, int R, int ql, int qr,
                long long a0, long long a1, long long a2, long long a3) {
        if (qr < L || R < ql) return;
        if (ql <= L && R <= qr) {
            apply(idx, L, R, a0, a1, a2, a3);
            return;
        }
        push(idx, L, R);
        int mid = (L + R) >> 1;
        update(idx<<1, L, mid, ql, qr, a0, a1, a2, a3);
        update(idx<<1|1, mid+1, R, ql, qr, a0, a1, a2, a3);
        t[idx].sum = t[idx<<1].sum + t[idx<<1|1].sum;
        if (t[idx].sum >= MOD) t[idx].sum -= MOD;
    }

    long long query(int idx, int L, int R, int ql, int qr) {
        if (qr < L || R < ql) return 0;
        if (ql <= L && R <= qr) return t[idx].sum;
        push(idx, L, R);
        int mid = (L + R) >> 1;
        long long left = query(idx<<1, L, mid, ql, qr);
        long long right = query(idx<<1|1, mid+1, R, ql, qr);
        long long res = left + right;
        if (res >= MOD) res -= MOD;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n >> K >> Q)) return 0;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long x; cin >> x;
        a[i] = x % MOD;
    }

    // prefix sums of powers
    S1.assign(n + 1, 0);
    S2.assign(n + 1, 0);
    S3.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        S1[i] = (S1[i-1] + i) % MOD;
        S2[i] = (S2[i-1] + 1LL*i*i) % MOD;
        S3[i] = (S3[i-1] + 1LL*i*i%MOD*i) % MOD;
    }

    // binomial coefficients up to 3
    long long C[4][4] = {{0}};
    for (int i = 0; i <= 3; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }

    SegTree seg(n);
    seg.build(1, 1, n);

    for (int qq = 0; qq < Q; ++qq) {
        int c, l, r;
        cin >> c >> l >> r;
        if (c == 1) {                     // update
            long long d = (MOD - ((l-1)%MOD)) % MOD;   // -(l-1) mod MOD
            long long coeff[4] = {0,0,0,0};
            for (int j = 0; j <= K; ++j) {
                // d^(K-j)
                long long pw = 1;
                for (int t = 0; t < K - j; ++t) pw = pw * d % MOD;
                coeff[j] = C[K][j] % MOD * pw % MOD;
            }
            seg.update(1, 1, n, l, r,
                       coeff[0], coeff[1], coeff[2], coeff[3]);
        } else {                          // query
            long long ans = seg.query(1, 1, n, l, r);
            cout << ans % MOD << '\n';
        }
    }
    return 0;
}
