#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

struct Fenwick {
    int n;
    vector<i128> b1, b2;
    Fenwick(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        b1.assign(n + 2, 0);
        b2.assign(n + 2, 0);
    }
    void add(vector<i128> &bit, int idx, i128 val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    i128 sum(const vector<i128> &bit, int idx) const {
        i128 s = 0;
        for (; idx > 0; idx -= idx & -idx) s += bit[idx];
        return s;
    }
    // add val to [l, r]
    void range_add(int l, int r, i128 val) {
        add(b1, l, val);
        add(b1, r + 1, -val);
        add(b2, l, val * (l - 1));
        add(b2, r + 1, -val * r);
    }
    // prefix sum 1..x
    i128 prefix_sum(int x) const {
        i128 s1 = sum(b1, x);
        i128 s2 = sum(b2, x);
        return s1 * x - s2;
    }
};

int gcd_int(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// sparse table for range gcd
struct GcdSparse {
    int n, LOG;
    vector<vector<int>> st;
    vector<int> lg2;
    GcdSparse(const vector<int> &a) {
        n = (int)a.size() - 1;               // a is 1-indexed
        LOG = 1;
        while ((1 << LOG) <= n) ++LOG;
        st.assign(LOG, vector<int>(n + 1));
        for (int i = 1; i <= n; ++i) st[0][i] = a[i];
        for (int k = 1; k < LOG; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                st[k][i] = gcd_int(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
        lg2.assign(n + 2, 0);
        for (int i = 2; i <= n + 1; ++i) lg2[i] = lg2[i >> 1] + 1;
    }
    int query(int l, int r) const { // inclusive, 1-indexed
        int k = lg2[r - l + 1];
        return gcd_int(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

string toString(i128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back('0' + digit);
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    while (cin >> N >> Q) {
        vector<int> a(N + 1);
        for (int i = 1; i <= N; ++i) cin >> a[i];

        // read queries
        vector<vector<pair<int,int>>> byL(N + 2);
        vector<i128> ans(Q);
        for (int i = 0; i < Q; ++i) {
            int L, R;
            cin >> L >> R;
            byL[L].push_back({R, i});
        }

        GcdSparse gst(a);
        Fenwick bit(N);

        // process left endpoints from N down to 1
        for (int L = N; L >= 1; --L) {
            int pos = L;
            while (pos <= N) {
                int cur_g = gst.query(L, pos);
                // binary search maximal r with same gcd
                int lo = pos, hi = N, best = pos;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    if (gst.query(L, mid) == cur_g) {
                        best = mid;
                        lo = mid + 1;
                    } else hi = mid - 1;
                }
                bit.range_add(pos, best, (i128)cur_g);
                pos = best + 1;
            }
            // answer queries whose left endpoint is L
            for (auto &qr : byL[L]) {
                int R = qr.first;
                int idx = qr.second;
                ans[idx] = bit.prefix_sum(R);
            }
        }

        for (int i = 0; i < Q; ++i) {
            cout << toString(ans[i]) << '\n';
        }
    }
    return 0;
}
