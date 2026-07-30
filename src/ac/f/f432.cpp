#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

__int128 S(ll a, ll b) {
    if (a < 0 || b < 0) return 0;
    if (a > b) swap(a, b);
    __int128 term1 = (__int128)(a + 1) * b * (b + 1) / 2;
    __int128 term2 = (__int128)a * (a + 1) * (a + 2) / 6;
    return term1 + term2;
}

__int128 calc_pos(ll u1, ll u2, ll v1, ll v2) {
    if (u1 > u2 || v1 > v2) return 0;
    __int128 sum_max = S(u2, v2) - S(u1 - 1, v2) - S(u2, v1 - 1) + S(u1 - 1, v1 - 1);
    ll cnt = (u2 - u1 + 1) * (v2 - v1 + 1);
    return sum_max + cnt;
}

vector<pair<ll, ll>> split_range(ll L, ll R) {
    vector<pair<ll, ll>> res;
    if (L > R) return res;
    if (L >= 0) {
        res.push_back({L, R});
    } else if (R <= 0) {
        res.push_back({-R, -L});
    } else {
        res.push_back({1, -L});
        res.push_back({0, R});
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, a, b, c, d;
    while (cin >> N) {
        cin >> a >> b >> c >> d;
        ll x1 = min(a, c) - N;
        ll x2 = max(a, c) - N;
        ll y1 = min(b, d) - N;
        ll y2 = max(b, d) - N;
        auto xs = split_range(x1, x2);
        auto ys = split_range(y1, y2);
        __int128 ans = 0;
        for (auto &xp : xs) {
            for (auto &yp : ys) {
                ans += calc_pos(xp.first, xp.second, yp.first, yp.second);
            }
        }
        ll mod = 1000000000;
        cout << (ll)(ans % mod) << '\n';
    }
    return 0;
}
