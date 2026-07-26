#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum;   // Σ a[i]
    long long mn;    // min a[i]
    long long mx;    // max a[i]
    long long pos;   // Σ max(0,a[i])  (valid only when uniform)
    long long lazy;  // pending addition
    int len;         // segment length
    Node() : sum(0), mn(0), mx(0), pos(0), lazy(0), len(0) {}
};

class SegTree {
    vector<Node> t;
    int n;
public:
    SegTree(const vector<long long>& a) {
        n = (int)a.size() - 1;               // a is 1‑based
        t.resize(4 * n + 5);
        build(1, 1, n, a);
    }

    void range_add(int l, int r, long long delta) { add(1, 1, n, l, r, delta); }
    long long range_query(int l, int r) { return query(1, 1, n, l, r); }

private:
    void build(int v, int L, int R, const vector<long long>& a) {
        t[v].lazy = 0;
        t[v].len = R - L + 1;
        if (L == R) {
            long long val = a[L];
            t[v].sum = t[v].mn = t[v].mx = val;
            t[v].pos = max(0LL, val);
            return;
        }
        int M = (L + R) >> 1;
        build(v << 1, L, M, a);
        build(v << 1 | 1, M + 1, R, a);
        pull(v);
    }

    // apply addition to a node, without descending
    void apply(int v, long long delta) {
        Node &nd = t[v];
        nd.sum  += delta * nd.len;
        nd.mn   += delta;
        nd.mx   += delta;
        nd.lazy += delta;
        if (nd.mn >= 0) nd.pos = nd.sum;
        else if (nd.mx <= 0) nd.pos = 0;
        // otherwise pos stays unchanged (will be recomputed later)
    }

    void push(int v) {
        long long lz = t[v].lazy;
        if (lz != 0) {
            apply(v << 1, lz);
            apply(v << 1 | 1, lz);
            t[v].lazy = 0;
        }
    }

    void pull(int v) {
        const Node &L = t[v << 1];
        const Node &R = t[v << 1 | 1];
        Node &nd = t[v];
        nd.sum = L.sum + R.sum;
        nd.mn  = min(L.mn, R.mn);
        nd.mx  = max(L.mx, R.mx);
        if (nd.mn >= 0) nd.pos = nd.sum;
        else if (nd.mx <= 0) nd.pos = 0;
        else nd.pos = L.pos + R.pos;
    }

    void add(int v, int L, int R, int ql, int qr, long long delta) {
        if (qr < L || R < ql) return;
        if (ql <= L && R <= qr) {
            long long newMn = t[v].mn + delta;
            long long newMx = t[v].mx + delta;
            if (newMn >= 0) {                 // whole segment becomes non‑negative
                apply(v, delta);
                t[v].pos = t[v].sum;
                return;
            }
            if (newMx <= 0) {                 // whole segment becomes non‑positive
                apply(v, delta);
                t[v].pos = 0;
                return;
            }
            // mixed after addition – need to go deeper
        }
        push(v);
        int M = (L + R) >> 1;
        add(v << 1, L, M, ql, qr, delta);
        add(v << 1 | 1, M + 1, R, ql, qr, delta);
        pull(v);
    }

    long long query(int v, int L, int R, int ql, int qr) {
        if (qr < L || R < ql) return 0;
        if (ql <= L && R <= qr) {
            if (t[v].mn >= 0) return t[v].sum;
            if (t[v].mx <= 0) return 0;
            // mixed – must descend
        }
        push(v);
        int M = (L + R) >> 1;
        return query(v << 1, L, M, ql, qr) +
               query(v << 1 | 1, M + 1, R, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    while (cin >> N >> K) {
        vector<long long> a(N + 1);
        for (int i = 1; i <= N; ++i) cin >> a[i];
        SegTree st(a);
        for (int q = 0; q < K; ++q) {
            char op; cin >> op;
            if (op == 'C') {
                int i, j; cin >> i >> j;
                cout << st.range_query(i, j) << '\n';
            } else {
                int i, j; long long x; cin >> i >> j >> x;
                if (op == '+')
                    st.range_add(i, j, x);
                else                // op == '-'
                    st.range_add(i, j, -x);
            }
        }
    }
    return 0;
}
