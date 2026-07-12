#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<pair<int, int>>> adj(N);
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }

        int A, B;
        cin >> A >> B;

        vector<int> dist(N, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[A] = 0;
        pq.push(make_pair(0, A));

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                int new_dist = max(dist[u], w);
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        if (dist[B] == INF) {
            cout << -1 << "\n";
        } else {
            cout << dist[B] << "\n";
        }
    }

    return 0;
}
