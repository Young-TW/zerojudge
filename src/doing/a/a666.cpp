#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

struct Edge {
    int to, cost;
    Edge(int t, int c) : to(t), cost(c) {}
};

vector<vector<Edge>> graph;
vector<int> dist;
vector<bool> visited;

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist.assign(graph.size(), 1e9);
    visited.assign(graph.size(), false);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& e : graph[u]) {
            int v = e.to;
            int cost = e.cost;
            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, K;
        cin >> n >> K;
        graph.clear();
        graph.resize(n + 1);
        vector<int> p(n + 1), t(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> p[i] >> t[i];
            graph[i].emplace_back(p[i], t[i]);
            graph[p[i]].emplace_back(i, t[i]);
        }

        vector<vector<int>> dists(n + 1);
        for (int i = 1; i <= n; ++i) {
            dijkstra(i);
            dists[i] = dist;
        }

        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (dists[i][j] <= K) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
