#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

struct Line {
    int64 m;   // slope
    int64 c;   // intercept
    Line(int64 _m = 0, int64 _c = -(1LL << 62)) : m(_m), c(_c) {}
};

struct LiChao {
    vector<Line> seg;
    vector<int64> xs;          // sorted unique x-coordinates
    const int64 NEG_INF = -(1LL << 62);

    LiChao(const vector<int64>& _xs) : xs(_xs) {
        seg.assign(4 * xs.size(), Line(0, NEG_INF));
    }

    inline i128 f(const Line& L, int64 x) const {
        return (i128)L.m * (i128)x + (i128)L.c;
    }

    void add_line(Line nw, int node, int l, int r) {
        int mid = (l + r) >> 1;
        int64 xl = xs[l];
        int64 xr = xs[r];
        int64 xm = xs[mid];

        Line cur = seg[node];
        // keep the line which is better at xm in the node
        if (f(nw, xm) > f(cur, xm)) {
            swap(nw, cur);
            seg[node] = cur;
        } else {
            seg[node] = cur;
        }

        if (l == r) return;

        if (f(nw, xl) > f(seg[node], xl)) {
            add_line(nw, node << 1, l, mid);
        } else if (f(nw, xr) > f(seg[node], xr)) {
            add_line(nw, node << 1 | 1, mid + 1, r);
        }
    }

    void add_line(const Line& L) { add_line(L, 1, 0, (int)xs.size() - 1); }

    int64 query(int64 x, int idx, int node, int l, int r) const {
        int64 cur = (int64)f(seg[node], x);
        if (l == r) return cur;
        int mid = (l + r) >> 1;
        if (idx <= mid)
            return max(cur, query(x, idx, node << 1, l, mid));
        else
            return max(cur, query(x, idx, node << 1 | 1, mid + 1, r));
    }

    int64 query(int64 x) const {
        int idx = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        return query(x, idx, 1, 0, (int)xs.size() - 1);
    }
};

void print_int128(i128 x) {
    if (x == 0) { cout << 0; return; }
    if (x < 0) { cout << '-'; x = -x; }
    string s;
    while (x > 0) {
        int d = x % 10;
        s.push_back('0' + d);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int64> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    vector<int64> S(n + 1, 0);          // prefix sum of a
    vector<int64> T(n + 1, 0);          // prefix sum of (i+1)*a_i
    for (int i = 1; i <= n; ++i) {
        S[i] = S[i - 1] + a[i];
        T[i] = T[i - 1] + (int64)(i + 1) * a[i];
    }

    // collect all x = S[i]
    vector<int64> xs = S;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    LiChao lichao(xs);
    // initial line for j = 0 : m = -1, c = 0
    lichao.add_line(Line(-1, 0));

    vector<int64> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int64 best = lichao.query(S[i]);          // max (m_j * S[i] + c_j)
        dp[i] = T[i] + best;                      // dp[i] fits in int64
        // prepare line for this i (j = i)
        int64 m = b[i] - (int64)i - 1;             // slope
        i128 c128 = (i128)dp[i] - (i128)T[i] - (i128)m * (i128)S[i];
        int64 c = (int64)c128;                    // fits in 64-bit
        lichao.add_line(Line(m, c));
    }

    i128 ans = dp[n];
    print_int128(ans);
    cout << '\n';
    return 0;
}
