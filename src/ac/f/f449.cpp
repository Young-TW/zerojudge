#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

typedef long long ll;
typedef __int128 i128;

const ll MOD = 1000000000LL;

i128 rs(ll x, ll y) {
    if (x <= 0 || y <= 0) return 0;
    if (x > y) swap(x, y);
    i128 part1 = (i128)x * (x + 1) * (4 * x - 1) / 6;
    ll diff = y * (y + 1) - x * (x + 1);
    i128 part2 = (i128)x * (diff / 2);
    return part1 + part2;
}

i128 solve_block(ll xl, ll xr, ll yl, ll yr) {
    ll u1, u2;
    if (xl >= 0) { u1 = xl; u2 = xr; }
    else { u1 = -xr; u2 = -xl; }
    ll v1, v2;
    if (yl >= 0) { v1 = yl; v2 = yr; }
    else { v1 = -yr; v2 = -yl; }
    return rs(u2 + 1, v2 + 1) - rs(u1, v2 + 1) - rs(u2 + 1, v1) + rs(u1, v1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, x1, y1, x2, y2;
    while (cin >> n >> x1 >> y1 >> x2 >> y2) {
        x1 -= n; y1 -= n; x2 -= n; y2 -= n;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        
        vector<pair<ll,ll>> xsegs;
        if (x1 < 0) xsegs.push_back({x1, min(x2, -1LL)});
        if (x2 >= 0) xsegs.push_back({max(x1, 0LL), x2});
        
        vector<pair<ll,ll>> ysegs;
        if (y1 < 0) ysegs.push_back({y1, min(y2, -1LL)});
        if (y2 >= 0) ysegs.push_back({max(y1, 0LL), y2});
        
        i128 total = 0;
        for (auto &xs : xsegs) {
            for (auto &ys : ysegs) {
                total += solve_block(xs.first, xs.second, ys.first, ys.second);
            }
        }
        ll ans = (ll)(total % MOD);
        cout << ans << '\n';
    }
    return 0;
}
