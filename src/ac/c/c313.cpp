#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <functional>
#include <numeric>
#include <queue>

using namespace std;

const int MAXN = 100005;
const int LOG = 20;

vector<pair<int, int>> adj[MAXN];
int up[MAXN][LOG];
int mx[MAXN][LOG];
int depth[MAXN];

void bfs(int root) {
    queue<int> q;
    q.push(root);
    depth[root] = 0;
    up[root][0] = -1;
    mx[root][0] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int i = 1; i < LOG; ++i) {
            if (up[u][i-1] != -1) {
                up[u][i] = up[up[u][i-1]][i-1];
                mx[u][i] = max(mx[u][i-1], mx[up[u][i-1]][i-1]);
            } else {
                up[u][i] = -1;
                mx[u][i] = 0;
            }
        }
        
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (v != up[u][0]) {
                up[v][0] = u;
                mx[v][0] = w;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
}

int query(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    int ans = 0;
    
    for (int i = 0; i < LOG; ++i) {
        if ((diff >> i) & 1) {
            ans = max(ans, mx[u][i]);
            u = up[u][i];
        }
    }
    
    if (u == v) return ans;
    
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            ans = max(ans, max(mx[u][i], mx[v][i]));
            u = up[u][i];
            v = up[v][i];
        }
    }
    
    ans = max(ans, max(mx[u][0], mx[v][0]));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        
        for (int i = 0; i < n - 1; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        bfs(1);
        
        int q;
        cin >> q;
        while (q--) {
            int a, b;
            cin >> a >> b;
            cout << query(a, b) << "\n";
        }
    }
    
    return 0;
}
