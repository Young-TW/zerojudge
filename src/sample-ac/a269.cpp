#include <vector>
#include <queue>
#include <array>
#include <climits>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0) break;
        vector<vector<pair<int,int>>> adj(n + 1); // to, length
        vector<array<int,4>> edges(m); // u, v, d, c
        for (int i = 0; i < m; i++) {
            int u, v, d, c;
            cin >> u >> v >> d >> c;
            edges[i] = {u, v, d, c};
            adj[u].push_back({v, d});
            adj[v].push_back({u, d});
        }

        const long long INF = 1e18;
        vector<long long> dist(n + 1, INF);
        dist[1] = 0;
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
        pq.push({0, 1});
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du > dist[u]) continue;
            for (auto& [v, d] : adj[u]) {
                if (dist[u] + d < dist[v]) {
                    dist[v] = dist[u] + d;
                    pq.push({dist[v], v});
                }
            }
        }

        vector<long long> bestCost(n + 1, LLONG_MAX);
        for (auto& e : edges) {
            int u = e[0], v = e[1], d = e[2], c = e[3];
            if (dist[u] + d == dist[v]) bestCost[v] = min(bestCost[v], (long long)c);
            if (dist[v] + d == dist[u]) bestCost[u] = min(bestCost[u], (long long)c);
        }

        long long total = 0;
        for (int v = 2; v <= n; v++) total += bestCost[v];
        cout << total << "\n";
    }

    return 0;
}
