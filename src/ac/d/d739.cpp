#include <iostream>
#include <vector>

using namespace std;

bool dfs(int u, const vector<vector<int>>& adj, vector<int>& match, vector<int>& vis, int vtag) {
    for (int v : adj[u]) {
        if (vis[v] != vtag) {
            vis[v] = vtag;
            if (match[v] == 0 || dfs(match[v], adj, match, vis, vtag)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            if (u >= 1 && u <= n && v >= 1 && v <= n) {
                adj[u].push_back(v);
            }
        }
        vector<int> match(n + 1, 0);
        vector<int> vis(n + 1, 0);
        int vtag = 0;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            vtag++;
            if (dfs(i, adj, match, vis, vtag)) {
                ans++;
            }
        }
        cout << n - ans << "\n";
    }
    return 0;
}
