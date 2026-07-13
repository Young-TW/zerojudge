#include <bits/stdc++.h>
using namespace std;

const long long INF = (long long)4e18;   // 足夠大的正無窮

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m;
    string type;
    while (cin >> n >> m >> type) {
        vector<long long> cost(n + 1);
        for (int i = 1; i <= n; ++i) cin >> cost[i];

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // 建立以 1 為根的父子關係與後序順序
        vector<int> parent(n + 1, 0);
        vector<vector<int>> child(n + 1);
        vector<int> order; order.reserve(n);
        stack<int> st;
        st.push(1);
        parent[1] = -1;
        while (!st.empty()) {
            int u = st.top(); st.pop();
            order.push_back(u);
            for (int v : adj[u]) if (v != parent[u]) {
                parent[v] = u;
                child[u].push_back(v);
                st.push(v);
            }
        }
        // 轉為後序 (子節點先處理)
        reverse(order.begin(), order.end());

        vector<long long> dp0(n + 1), dp1(n + 1);
        for (int qi = 0; qi < m; ++qi) {
            int a, x, b, y;
            cin >> a >> x >> b >> y;
            // 檢查同一節點衝突
            if (a == b && x != y) {
                cout << -1 << '\n';
                continue;
            }

            vector<int> forced(n + 1, -1);
            forced[a] = x;
            forced[b] = y;

            bool impossible = false;
            for (int u : order) {
                long long d0 = (forced[u] == 1) ? INF : 0;          // u 不選的成本
                long long d1 = (forced[u] == 0) ? INF : cost[u];   // u 選的成本

                for (int v : child[u]) {
                    // 若 u 不選，子必選
                    if (d0 < INF) {
                        if (dp1[v] >= INF) d0 = INF;
                        else {
                            d0 += dp1[v];
                            if (d0 > INF) d0 = INF;
                        }
                    }
                    // 若 u 選，子可選可不選
                    if (d1 < INF) {
                        long long best = min(dp0[v], dp1[v]);
                        if (best >= INF) d1 = INF;
                        else {
                            d1 += best;
                            if (d1 > INF) d1 = INF;
                        }
                    }
                }
                dp0[u] = d0;
                dp1[u] = d1;
                if (dp0[u] >= INF && dp1[u] >= INF) {
                    // 子樹已無可行解，整體必不可能
                    // 仍繼續計算，以免影響其他查詢
                }
            }
            long long ans = min(dp0[1], dp1[1]);
            if (ans >= INF/2) cout << -1 << '\n';
            else cout << ans << '\n';
        }
    }
    return 0;
}
