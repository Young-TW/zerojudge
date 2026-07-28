#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Fenwick2D {
    int N;                                   // number of distinct x
    vector<long long> xs;                    // compressed x values (sorted)
    vector< vector<ll> > yVals;              // y values for each node
    vector< vector<ll> > bit;                // inner BITs

    Fenwick2D(const vector<pair<ll,ll>>& points) {
        // collect distinct x from update points only
        xs.reserve(points.size());
        for (auto &p : points) xs.push_back(p.first);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        N = (int)xs.size();

        yVals.assign(N + 1, vector<ll>());
        // fill yVals
        for (auto &p : points) {
            int cx = (int)(lower_bound(xs.begin(), xs.end(), p.first) - xs.begin()) + 1;
            for (int i = cx; i <= N; i += i & -i)
                yVals[i].push_back(p.second);
        }
        // sort & unique, allocate inner BITs
        bit.resize(N + 1);
        for (int i = 1; i <= N; ++i) {
            auto &v = yVals[i];
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            bit[i].assign(v.size() + 1, 0);
        }
    }

    // add delta at point (x, y)   (x is guaranteed to be in xs)
    void add(ll x, ll y, ll delta) {
        int cx = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin()) + 1;
        for (int i = cx; i <= N; i += i & -i) {
            int cy = (int)(lower_bound(yVals[i].begin(), yVals[i].end(), y) - yVals[i].begin()) + 1;
            for (int j = cy; j < (int)bit[i].size(); j += j & -j)
                bit[i][j] += delta;
        }
    }

    // prefix sum S(X, Y) = sum of all points with x <= X and y <= Y
    ll sumPrefix(ll X, ll Y) const {
        ll res = 0;
        int cx = (int)(upper_bound(xs.begin(), xs.end(), X) - xs.begin()); // number of xs <= X
        for (int i = cx; i > 0; i -= i & -i) {
            int cy = (int)(upper_bound(yVals[i].begin(), yVals[i].end(), Y) - yVals[i].begin());
            for (int j = cy; j > 0; j -= j & -j)
                res += bit[i][j];
        }
        return res;
    }

    // rectangle sum [x1..x2] × [y1..y2] (inclusive)
    ll queryRect(ll x1, ll y1, ll x2, ll y2) const {
        if (x1 > x2 || y1 > y2) return 0;
        ll a = sumPrefix(x2, y2);
        ll b = sumPrefix(x1 - 1, y2);
        ll c = sumPrefix(x2, y1 - 1);
        ll d = sumPrefix(x1 - 1, y1 - 1);
        return a - b - c + d;
    }
};

struct Op {
    int type;          // 1 = update, 2 = query
    ll a, b, c, d;     // meaning depends on type
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    if (!(cin >> q)) return 0;
    vector<Op> ops;
    ops.reserve(q);
    vector<pair<ll,ll>> updPoints;          // only update points for compression
    for (int i = 0; i < q; ++i) {
        int t; cin >> t;
        if (t == 1) {
            ll x, y, k; cin >> x >> y >> k;
            ops.push_back({1, x, y, k, 0});
            updPoints.emplace_back(x, y);
        } else {
            ll u, d, l, r; cin >> u >> d >> l >> r;
            ops.push_back({2, u, d, l, r});
        }
    }

    Fenwick2D ft(updPoints);

    for (const auto &op : ops) {
        if (op.type == 1) {
            ft.add(op.a, op.b, op.c);          // a=x, b=y, c=k
        } else {
            ll ans = ft.queryRect(op.a, op.c, op.b, op.d); // u,l,d,r
            cout << ans << '\n';
        }
    }
    return 0;
}
