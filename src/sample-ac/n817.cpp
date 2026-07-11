#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int V;
    while (cin >> V && V) {
        vector<vector<int>> adj(V + 1);
        int a, b;
        while (cin >> a >> b && (a || b)) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        vector<int> color(V + 1, -1);
        bool is_bipartite = true;
        
        for (int i = 1; i <= V; ++i) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int v : adj[u]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            is_bipartite = false;
                            break;
                        }
                    }
                    if (!is_bipartite) break;
                }
            }
            if (!is_bipartite) break;
        }
        
        if (is_bipartite) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
