#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<int> dist(N + 1, -1);
        vector<char> is_marked(N + 1, 0);
        
        queue<int> q;
        q.push(1);
        dist[1] = 0;
        
        vector<int> unvisited;
        vector<int> next_unvisited;
        unvisited.reserve(N > 1 ? N - 1 : 0);
        next_unvisited.reserve(N > 1 ? N - 1 : 0);
        
        for (int i = 2; i <= N; ++i) {
            unvisited.push_back(i);
        }
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    is_marked[v] = 1;
                }
            }
            
            next_unvisited.clear();
            for (int v : unvisited) {
                if (is_marked[v]) {
                    next_unvisited.push_back(v);
                } else {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
            unvisited.swap(next_unvisited);
            
            for (int v : unvisited) {
                is_marked[v] = 0;
            }
        }
        
        cout << dist[N] << "\n";
    }
    
    return 0;
}
