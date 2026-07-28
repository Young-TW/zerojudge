#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int K, M, N, P;
    while (cin >> K >> M >> N >> P) {
        struct Edge {int u, v, w;};
        vector<Edge> edges;
        edges.reserve(P);
        vector<vector<int>> adj(K + 1);
        for (int i = 0; i < P; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            edges.push_back({a, b, w});
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        // BFS from node 1
        vector<char> vis(K + 1, 0);
        queue<int> q;
        q.push(1);
        vis[1] = 1;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (int nb : adj[cur]) {
                if (!vis[nb]) {
                    vis[nb] = 1;
                    q.push(nb);
                }
            }
        }
        long long total = 0;
        for (const auto &e : edges) {
            if (vis[e.u] && vis[e.v]) total += e.w;
        }
        long long limit = 1LL * N * M;
        long long ans = (total < limit) ? total : limit;
        cout << ans << "\n";
    }
    return 0;
}
