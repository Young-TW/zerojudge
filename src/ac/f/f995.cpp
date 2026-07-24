#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long m, c;                     // y = m * x + c
    Line(long long _m = 0, long long _c = LLONG_MIN) : m(_m), c(_c) {}
    long long get(long long x) const {
        return m * x + c;
    }
};

struct LiChaoNode {
    Line line;
    int l = 0, r = 0;
    bool has = false;
    LiChaoNode() {}
    LiChaoNode(const Line& ln) : line(ln), has(true) {}
};

struct LiChaoTree {
    vector<LiChaoNode> tr;
    long long X_MIN, X_MAX;
    LiChaoTree(long long xl, long long xr) : X_MIN(xl), X_MAX(xr) {
        tr.reserve(1);
        tr.emplace_back();               // index 0 = empty
    }

    void add_line(int &node, long long l, long long r, Line nw) {
        if (node == 0) {
            node = (int)tr.size();
            tr.emplace_back(nw);
            return;
        }
        long long mid = (l + r) >> 1;
        bool left = nw.get(l) > tr[node].line.get(l);
        bool middle = nw.get(mid) > tr[node].line.get(mid);
        if (middle) swap(nw, tr[node].line);
        if (l == r) return;
        if (left != middle) add_line(tr[node].l, l, mid, nw);
        else                add_line(tr[node].r, mid + 1, r, nw);
    }

    void add_line(int &node, Line nw) {
        add_line(node, X_MIN, X_MAX, nw);
    }

    long long query(int node, long long l, long long r, long long x) const {
        if (node == 0) return LLONG_MIN;
        long long cur = tr[node].line.get(x);
        if (l == r) return cur;
        long long mid = (l + r) >> 1;
        if (x <= mid) return max(cur, query(tr[node].l, l, mid, x));
        else          return max(cur, query(tr[node].r, mid + 1, r, x));
    }

    long long query(int node, long long x) const {
        return query(node, X_MIN, X_MAX, x);
    }
};

struct SegTree {
    int n;
    vector<int> root;          // root index of Li Chao tree for each segment node
    LiChaoTree &cht;           // reference to the global Li Chao structure (same domain for all)

    SegTree(int _n, LiChaoTree &global) : n(_n), cht(global) {
        root.assign(4 * (n + 1), 0);
    }

    // point update: insert line at position pos
    void insert(int idx, int l, int r, int pos, const Line &ln) {
        cht.add_line(root[idx], ln);
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (pos <= mid) insert(idx << 1, l, mid, pos, ln);
        else            insert(idx << 1 | 1, mid + 1, r, pos, ln);
    }

    void insert(int pos, const Line &ln) {
        insert(1, 0, n, pos, ln);
    }

    // range query on [ql,qr] for x
    long long query(int idx, int l, int r, int ql, int qr, long long x) const {
        if (qr < l || r < ql) return LLONG_MIN;
        if (ql <= l && r <= qr) {
            return cht.query(root[idx], x);
        }
        int mid = (l + r) >> 1;
        long long left = query(idx << 1, l, mid, ql, qr, x);
        long long right = query(idx << 1 | 1, mid + 1, r, ql, qr, x);
        return max(left, right);
    }

    long long query(int l, int r, long long x) const {
        if (l > r) return LLONG_MIN;
        return query(1, 0, n, l, r, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, K;
    if (!(cin >> n >> K)) return 0;
    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    vector<long long> S(n + 1, 0), T(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        S[i] = S[i - 1] + a[i];
        T[i] = T[i - 1] + (long long)i * a[i];
    }

    long long minX = *min_element(S.begin(), S.end());
    long long maxX = *max_element(S.begin(), S.end());

    LiChaoTree globalCht(minX, maxX);
    SegTree seg(n, globalCht);          // indices 0..n

    vector<long long> dp(n + 1, 0);
    // line for j = 0 : m = 0, c = 0
    seg.insert(0, Line(0, 0));

    for (int i = 1; i <= n; ++i) {
        int L = max(0, i - K);
        int R = i - 1;
        long long best = seg.query(L, R, S[i]);
        // best is never LLONG_MIN because K >= 1
        dp[i] = T[i] + best;

        long long m = b[i] - i;
        long long c = dp[i] - T[i] - m * S[i];
        seg.insert(i, Line(m, c));
    }

    cout << dp[n] << "\n";
    return 0;
}
