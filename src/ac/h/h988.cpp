#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF64 = (ll)4e18;

struct Edge {
    int to;
    int w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b, s;
    while (cin >> n >> m >> a >> b >> s) {
        --s;                                   // zero based
        vector<int> d(n), c(n);
        for (int i = 0; i < n; ++i) cin >> d[i];
        for (int i = 0; i < n; ++i) cin >> c[i];

        vector<vector<Edge>> adj(n);
        for (int i = 0; i < m; ++i) {
            int x, y, w;
            cin >> x >> y >> w;
            --x; --y;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }

        /* ---------- Dijkstra ---------- */
        vector<ll> dist(n, INF64);
        using P = pair<ll,int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        dist[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du != dist[u]) continue;
            for (auto &e : adj[u]) {
                ll nd = du + e.w;
                if (nd < dist[e.to]) {
                    dist[e.to] = nd;
                    pq.emplace(nd, e.to);
                }
            }
        }

        /* ---------- prepare v and g ---------- */
        vector<ll> v(n), g(n);
        for (int i = 0; i < n; ++i) {
            v[i] = dist[i];
            // g = (d-1)*v + c
            g[i] = (ll)(d[i] - 1) * v[i] + (ll)c[i];
        }

        /* ---------- binary search on lambda ---------- */
        ll low = -400000000000000LL;   // -4e14
        ll high = 400000000000000LL;   // 4e14
        auto count_black = [&](ll lambda)->pair<ll,int>{
            // returns (sumBest, cntBlack) for the a best vertices
            static vector<pair<ll,int>> arr; // (best, isBlack)
            arr.resize(n);
            for (int i = 0; i < n; ++i) {
                ll add = g[i] - lambda;
                if (add < 0) add = 0;
                arr[i].first = v[i] + add;
                arr[i].second = (g[i] > lambda) ? 1 : 0;
            }
            nth_element(arr.begin(), arr.begin() + a, arr.end(),
                        [](const pair<ll,int>& A, const pair<ll,int>& B){
                            return A.first > B.first;
                        });
            ll sum = 0;
            int cnt = 0;
            for (int i = 0; i < a; ++i) {
                sum += arr[i].first;
                cnt += arr[i].second;
            }
            return {sum, cnt};
        };

        while (low < high) {
            ll mid = (low + high + 1) >> 1;
            auto res = count_black(mid);
            if (res.second >= b) low = mid;
            else high = mid - 1;
        }
        ll lambda = low;                     // λ*

        /* ---------- final evaluation ---------- */
        // compute best values again and keep the a best vertices
        struct Item {
            ll best;
            ll v;
            ll g;
            bool isBlack; // g > lambda
        };
        vector<Item> items(n);
        for (int i = 0; i < n; ++i) {
            ll add = g[i] - lambda;
            if (add < 0) add = 0;
            items[i] = {v[i] + add, v[i], g[i], g[i] > lambda};
        }
        nth_element(items.begin(), items.begin() + a, items.end(),
                    [](const Item& A, const Item& B){
                        return A.best > B.best;
                    });
        ll sumV = 0;
        vector<ll> diffs; diffs.reserve(a);
        int cntBlack = 0;
        for (int i = 0; i < a; ++i) {
            sumV += items[i].v;
            if (items[i].isBlack) {
                ++cntBlack;
                diffs.push_back(items[i].g - lambda); // positive
            }
        }
        // we have cntBlack >= b, need to keep exactly b
        sort(diffs.begin(), diffs.end()); // ascending
        ll drop = 0;
        int toDrop = cntBlack - b;
        for (int i = 0; i < toDrop; ++i) drop += diffs[i];
        ll keptDiffSum = 0;
        for (ll dval : diffs) keptDiffSum += dval;
        keptDiffSum -= drop;

        ll answer = sumV + keptDiffSum + lambda * (ll)b;
        cout << answer << '\n';
    }
    return 0;
}
