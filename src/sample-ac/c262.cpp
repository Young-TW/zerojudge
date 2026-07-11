#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    while (cin >> n >> m >> q) {
        if (n == 0 && m == 0 && q == 0) break;
        
        const int INF = 2000000000;
        vector<vector<int>> adj(n + 1, vector<int>(n + 1, INF));
        
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            adj[a][b] = c;
            adj[b][a] = c;
        }
        
        vector<bool> visited(n + 1, false);
        queue<int> bfs;
        
        bfs.push(1);
        visited[1] = true;
        
        while (!bfs.empty()) {
            int u = bfs.front();
            bfs.pop();
            
            if (u == n) break;
            
            for (int v = 1; v <= n; ++v) {
                if (adj[u][v] != INF && adj[u][v] <= q && !visited[v]) {
                    visited[v] = true;
                    bfs.push(v);
                }
            }
        }
        
        if (visited[n]) {
            cout << "Save\n";
        } else {
            cout << "GG\n";
        }
    }
    
    return 0;
}
