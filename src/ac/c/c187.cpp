#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C;
    if (!(cin >> C)) return 0;
    
    for (int case_num = 1; case_num <= C; ++case_num) {
        int n, m, S, T;
        cin >> n >> m >> S >> T;
        
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[S] = 0;
        pq.push({0, S});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            if (u == T) break;
            
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        cout << "Case #" << case_num << ": ";
        if (dist[T] == INT_MAX) {
            cout << "unreachable\n";
        } else {
            cout << dist[T] << "\n";
        }
    }
    
    return 0;
}
