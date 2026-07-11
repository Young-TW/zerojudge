#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

const int MAXN = 5005;
vector<pair<int, int>> adj[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M, Y, O;
    while (cin >> N >> M >> Y >> O) {
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
        }
        
        for (int i = 0; i < M; ++i) {
            int a, b, x;
            cin >> a >> b >> x;
            adj[a].push_back({b, x});
            adj[b].push_back({a, x});
        }
        
        vector<int> dist(N + 1, 1000000000);
        dist[Y] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, Y});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        cout << dist[O] << "\n";
    }
    
    return 0;
}
