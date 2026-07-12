#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<vector<pair<int, int>>> adj(N);
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({w, v});
            adj[v].push_back({w, u});
        }
        
        long long total_cost = 0;
        int visited_count = 0;
        vector<bool> visited(N, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        pq.push({0, 0});
        
        while (!pq.empty() && visited_count < N) {
            pair<int, int> top = pq.top();
            pq.pop();
            
            int cost = top.first;
            int u = top.second;
            
            if (visited[u]) continue;
            visited[u] = true;
            visited_count++;
            total_cost += cost;
            
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int w = adj[u][i].first;
                int v = adj[u][i].second;
                if (!visited[v]) {
                    pq.push({w, v});
                }
            }
        }
        
        cout << total_cost << "\n";
    }
    
    return 0;
}
