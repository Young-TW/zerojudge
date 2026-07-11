#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int k = 0; k < T; ++k) {
        if (k) cout << "\n";
        
        int N, E, t, M;
        cin >> N >> E >> t >> M;
        
        vector<vector<pair<int, int>>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            adj[b].push_back({a, c});
        }
        
        vector<int> dist(N + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[E] = 0;
        pq.push({0, E});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            if (dist[i] <= t) {
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
