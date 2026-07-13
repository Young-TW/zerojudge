#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        if (n <= 0) continue;
        
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> down1(n, 0), down2(n, 0), best(n, -1), up(n, 0);
        vector<int> parent(n, -1);
        vector<int> order;
        order.reserve(n);
        
        queue<int> q;
        q.push(0);
        parent[0] = -2; // Mark as visited
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u]) {
                if (parent[v] == -1) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        int D = 0;
        // Process in reverse BFS order to compute down1 and down2
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                int val = down1[v] + 1;
                if (val > down1[u]) {
                    down2[u] = down1[u];
                    down1[u] = val;
                    best[u] = v;
                } else if (val > down2[u]) {
                    down2[u] = val;
                }
            }
            D = max(D, down1[u] + down2[u]);
        }

        // Process in BFS order to compute up
        for (int i = 0; i < n; ++i) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                if (v == best[u]) {
                    up[v] = max(up[u], down2[u]) + 1;
                } else {
                    up[v] = max(up[u], down1[u]) + 1;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (max(down1[i] + down2[i], down1[i] + up[i]) == D) {
                cout << i << "\n";
            }
        }
    }
    return 0;
}
