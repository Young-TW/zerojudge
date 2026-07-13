#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        int LOG = 17;
        vector<vector<int>> fa(N, vector<int>(LOG, -1));
        vector<int> depth(N, 0);
        vector<int> order;
        vector<bool> vis(N, false);
        
        queue<int> q;
        q.push(0);
        vis[0] = true;
        depth[0] = 0;
        fa[0][0] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    depth[v] = depth[u] + 1;
                    fa[v][0] = u;
                    q.push(v);
                }
            }
        }
        
        for (int i = 1; i < LOG; ++i) {
            for (int u : order) {
                if (fa[u][i-1] != -1) {
                    fa[u][i] = fa[fa[u][i-1]][i-1];
                } else {
                    fa[u][i] = -1;
                }
            }
        }
        
        auto getLCA = [&](int u, int v) -> int {
            if (depth[u] < depth[v]) swap(u, v);
            int diff = depth[u] - depth[v];
            for (int i = 0; i < LOG; ++i) {
                if ((diff >> i) & 1) {
                    u = fa[u][i];
                }
            }
            if (u == v) return u;
            for (int i = LOG - 1; i >= 0; --i) {
                if (fa[u][i] != fa[v][i]) {
                    u = fa[u][i];
                    v = fa[v][i];
                }
            }
            return fa[u][0];
        };
        
        vector<long long> diff(N, 0);
        for (int i = 0; i < M; ++i) {
            int u, v, k;
            cin >> u >> v >> k;
            int lca = getLCA(u, v);
            diff[u] += k;
            diff[v] += k;
            diff[lca] -= k;
            if (fa[lca][0] != -1) {
                diff[fa[lca][0]] -= k;
            }
        }
        
        for (int i = order.size() - 1; i >= 0; --i) {
            int u = order[i];
            if (fa[u][0] != -1) {
                diff[fa[u][0]] += diff[u];
            }
        }
        
        for (int i = 0; i < N; ++i) {
            cout << diff[i];
            if (i < N - 1) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
