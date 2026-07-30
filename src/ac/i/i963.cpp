#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

using int64 = long long;
using i128 = __int128;

const i128 NEG_INF = -( (i128)1 << 100 );

struct Line {
    int64 m;
    i128 c;
    Line() : m(0), c(0) {}
    Line(int64 _m, i128 _c) : m(_m), c(_c) {}
};

inline i128 value(const Line& L, int64 x) {
    return (i128)L.m * x + L.c;
}

class LiChao {
public:
    vector<int64> xs;
    vector<Line> seg;
    vector<int> timestamps;
    int cur_time;
    int sz;
    LiChao() : cur_time(0) {}
    void init(const vector<int64>& _xs) {
        xs = _xs;
        sz = xs.size();
        seg.assign(sz * 4 + 4, Line());
        timestamps.assign(sz * 4 + 4, 0);
        cur_time = 0;
    }
    void clear() {
        ++cur_time;
    }
    void add_line(Line nw, int node, int l, int r) {
        if (timestamps[node] != cur_time) {
            timestamps[node] = cur_time;
            seg[node] = nw;
            return;
        }
        int m = (l + r) >> 1;
        int64 xl = xs[l], xm = xs[m], xr = xs[r];
        Line &cur = seg[node];
        if (value(nw, xm) > value(cur, xm)) {
            Line tmp = nw; nw = cur; cur = tmp;
        }
        if (l == r) return;
        if (value(nw, xl) > value(cur, xl)) {
            add_line(nw, node << 1, l, m);
        } else if (value(nw, xr) > value(cur, xr)) {
            add_line(nw, node << 1 | 1, m + 1, r);
        }
    }
    void add_line(Line L) {
        if (sz == 0) return;
        add_line(L, 1, 0, sz - 1);
    }
    i128 query(int idx, int node, int l, int r) {
        if (timestamps[node] != cur_time) {
            return NEG_INF;
        }
        i128 best = value(seg[node], xs[idx]);
        if (l == r) return best;
        int m = (l + r) >> 1;
        if (idx <= m) {
            i128 left = query(idx, node << 1, l, m);
            if (left > best) best = left;
        } else {
            i128 right = query(idx, node << 1 | 1, m + 1, r);
            if (right > best) best = right;
        }
        return best;
    }
    i128 query_by_idx(int idx) {
        if (sz == 0) return NEG_INF;
        return query(idx, 1, 0, sz - 1);
    }
    i128 query(int64 x) {
        if (sz == 0) return NEG_INF;
        int idx = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        if (idx == sz || xs[idx] != x) return NEG_INF;
        return query(idx, 1, 0, sz - 1);
    }
};

string toString(i128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    string s;
    while (x > 0) {
        int d = (int)(x % 10);
        s.push_back('0' + d);
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, K;
    while (cin >> n >> K) {
        vector<int64> a(n+1), b(n+1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i];
        b[0] = 0;
        vector<int64> S1(n+1, 0), S2(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            S1[i] = S1[i-1] + a[i];
            S2[i] = S2[i-1] + (int64)i * a[i];
        }
        // a is no longer needed
        a.clear();
        vector<int64> xs = S1;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        vector<int> idx_of_S1(n+1);
        for (int i = 0; i <= n; ++i) {
            idx_of_S1[i] = lower_bound(xs.begin(), xs.end(), S1[i]) - xs.begin();
        }
        LiChao lichao;
        lichao.init(xs);
        vector<i128> dp(n+1, NEG_INF);
        vector<int64> slope(n+1, 0);
        dp[0] = 0;
        slope[0] = 0;
        auto solve = [&](auto&& self, int l, int r) -> void {
            if (l == r) {
                if (l == 0) return;
                if (dp[l] != NEG_INF) {
                    slope[l] = b[l] - l;
                } else {
                    slope[l] = 0;
                }
                return;
            }
            int mid = (l + r) >> 1;
            self(self, l, mid);
            // contributions from [l, mid] to [mid+1, r]
            lichao.clear();
            int p = mid;
            for (int i = r; i >= mid + 1; --i) {
                while (p >= l && p >= i - K) {
                    if (dp[p] != NEG_INF) {
                        i128 c = dp[p] - S2[p] - (i128)slope[p] * S1[p];
                        lichao.add_line(Line(slope[p], c));
                    }
                    --p;
                }
                i128 best = lichao.query_by_idx(idx_of_S1[i]);
                if (best != NEG_INF) {
                    i128 val = S2[i] + best;
                    if (val > dp[i]) dp[i] = val;
                }
            }
            self(self, mid + 1, r);
        };
        solve(solve, 0, n);
        cout << toString(dp[n]) << '\n';
    }
    return 0;
}
