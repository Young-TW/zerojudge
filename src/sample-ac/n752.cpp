#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            int u, k;
            char c;
            cin >> u >> c >> c >> k >> c;
            for (int j = 0; j < k; ++j) {
                int v;
                cin >> v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
        
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }

        vector<int> parent(n, -1);
        vector<bool> visited(n, false);
        vector<int> q;
        q.reserve(n);
        q.push_back(0);
        visited[0] = true;
        
        for (int i = 0; i < (int)q.size(); ++i) {
            int u = q[i];
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push_back(v);
                }
            }
        }
        
        vector<vector<int>> dp(n, vector<int>(2, 0));
        for (int i = (int)q.size() - 1; i >= 0; --i) {
            int u = q[i];
            dp[u][0] = 0;
            dp[u][1] = 1;
            for (int v : adj[u]) {
                if (v != parent[u]) {
                    dp[u][0] += dp[v][1];
                    dp[u][1] += min(dp[v][0], dp[v][1]);
                }
            }
        }
        
        cout << min(dp[0][0], dp[0][1]) << "\n";
    }
    return 0;
}
