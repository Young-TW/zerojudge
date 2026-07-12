#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 1e9;

void solve() {
    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<int> cost(N + 1, 0);
        // Read costs for cities 2 to N-1
        for (int i = 2; i <= N - 1; ++i) {
            cin >> cost[i];
        }

        vector<vector<pair<int, int>>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Precompute reachable nodes from each node within distance K
        vector<vector<int>> reachable(N + 1);
        for (int i = 1; i <= N; ++i) {
            vector<int> dist(N + 1, INF);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            
            dist[i] = 0;
            pq.push({0, i});
            
            while (!pq.empty()) {
                int d = pq.top().first;
                int u = pq.top().second;
                pq.pop();
                
                if (d > dist[u]) continue;
                if (d > K) break; // Optimization: since we only care about <= K
                
                reachable[i].push_back(u);
                
                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int w = edge.second;
                    if (dist[u] + w < dist[v] && dist[u] + w <= K) {
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        // Meta-Dijkstra
        vector<int> dist_meta(N + 1, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist_meta[1] = 0;
        pq.push({0, 1});
        
        int ans = -1;
        
        while (!pq.empty()) {
            int c = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (c > dist_meta[u]) continue;
            
            if (u == N) {
                ans = c;
                break;
            }
            
            for (int v : reachable[u]) {
                int new_cost = c + cost[v];
                if (new_cost < dist_meta[v]) {
                    dist_meta[v] = new_cost;
                    pq.push({new_cost, v});
                }
            }
        }
        
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
