#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        if (n == 1) {
            cout << a[1] << '\n';
            continue;
        }

        vector<int> deg(n + 1);
        for (int i = 1; i <= n; ++i) deg[i] = adj[i].size();

        vector<ll> max1(n + 1, 0), max2(n + 1, 0);
        vector<char> removed(n + 1, 0);
        ll ans = a[1];
        for (int i = 2; i <= n; ++i) if (a[i] > ans) ans = a[i];

        queue<int> q;
        for (int i = 1; i <= n; ++i) if (deg[i] == 1) q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            removed[u] = 1;
            ll g_u = a[u] + (max1[u] > 0 ? max1[u] : 0);
            ll cand = a[u] + (max1[u] > 0 ? max1[u] : 0) + (max2[u] > 0 ? max2[u] : 0);
            if (cand > ans) ans = cand;
            int p = -1;
            for (int v : adj[u]) {
                if (!removed[v]) {
                    p = v;
                    break;
                }
            }
            if (p != -1) {
                if (g_u > 0) {
                    if (g_u > max1[p]) {
                        max2[p] = max1[p];
                        max1[p] = g_u;
                    } else if (g_u > max2[p]) {
                        max2[p] = g_u;
                    }
                }
                deg[p]--;
                if (deg[p] == 1 && !removed[p]) {
                    q.push(p);
                }
            }
        }

        vector<int> cycle;
        for (int i = 1; i <= n; ++i) if (!removed[i]) cycle.push_back(i);
        if (cycle.empty()) {
            cout << ans << '\n';
            continue;
        }

        int k = cycle.size();
        vector<int> order;
        int start = cycle[0];
        int cur = start, prev = -1;
        do {
            order.push_back(cur);
            for (int nxt : adj[cur]) {
                if (!removed[nxt] && nxt != prev) {
                    prev = cur;
                    cur = nxt;
                    break;
                }
            }
        } while (cur != start);

        vector<ll> A(k), B(k);
        for (int i = 0; i < k; ++i) {
            int v = order[i];
            A[i] = a[v];
            B[i] = a[v] + (max1[v] > 0 ? max1[v] : 0);
            ll cand = a[v] + (max1[v] > 0 ? max1[v] : 0) + (max2[v] > 0 ? max2[v] : 0);
            if (cand > ans) ans = cand;
        }

        if (k >= 2) {
            vector<ll> A2(2 * k), B2(2 * k);
            for (int i = 0; i < 2 * k; ++i) {
                A2[i] = A[i % k];
                B2[i] = B[i % k];
            }
            vector<ll> P(2 * k + 1, 0);
            for (int i = 0; i < 2 * k; ++i) {
                P[i + 1] = P[i] + A2[i];
            }
            deque<pair<int, ll>> dq;
            for (int R = 0; R < 2 * k; ++R) {
                while (!dq.empty() && dq.front().first < R - k + 1) {
                    dq.pop_front();
                }
                if (!dq.empty() && R > 0) {
                    ll cand = dq.front().second + B2[R] + P[R];
                    if (cand > ans) ans = cand;
                }
                ll cur_val = B2[R] - P[R + 1];
                while (!dq.empty() && dq.back().second <= cur_val) {
                    dq.pop_back();
                }
                dq.push_back(make_pair(R, cur_val));
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
