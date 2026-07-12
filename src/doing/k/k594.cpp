#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef long long ll;

struct Fenwick2D {
    map<ll, map<ll, ll>> tree;

    void update(ll x, ll y, ll delta) {
        for (ll i = x; i <= 1e9; i += i & -i) {
            for (ll j = y; j <= 1e9; j += j & -j) {
                tree[i][j] += delta;
            }
        }
    }

    ll query(ll x, ll y) {
        ll res = 0;
        for (ll i = x; i > 0; i -= i & -i) {
            for (ll j = y; j > 0; j -= j & -j) {
                if (tree.find(i) != tree.end() && tree[i].find(j) != tree[i].end()) {
                    res += tree[i][j];
                }
            }
        }
        return res;
    }

    ll query(ll x1, ll y1, ll x2, ll y2) {
        return query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    Fenwick2D fenwick;

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            ll x, y, k;
            cin >> x >> y >> k;
            fenwick.update(x, y, k);
        } else {
            ll u, d, l, r;
            cin >> u >> d >> l >> r;
            cout << fenwick.query(u, l, d, r) << '\n';
        }
    }

    return 0;
}
