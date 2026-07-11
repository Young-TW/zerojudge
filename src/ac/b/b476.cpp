#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    bool first = true;
    while (cin >> n >> m) {
        if (!first) cout << "\n";
        first = false;
        
        vector<vector<int>> adj(n + 1), radj(n + 1);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            radj[y].push_back(x);
        }
        int s, t;
        cin >> s >> t;
        
        // BFS from t on reverse graph: find all nodes that can reach t
        vector<bool> canReach(n + 1, false);
        queue<int> q;
        canReach[t] = true;
        q.push(t);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : radj[u]) {
                if (!canReach[v]) {
                    canReach[v] = true;
                    q.push(v);
                }
            }
        }
        
        // A node is valid if all its out-neighbors can reach t
        vector<bool> valid(n + 1, true);
        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                if (!canReach[v]) {
                    valid[u] = false;
                    break;
                }
            }
        }
        
        // BFS from s to t on valid nodes only
        vector<int> dist(n + 1, -1);
        if (valid[s]) {
            dist[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (valid[v] && dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }
        }
        
        cout << dist[t] << "\n";
    }
    
    return 0;
}
