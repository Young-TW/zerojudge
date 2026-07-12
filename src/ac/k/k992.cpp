#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 100005;
const int LOG = 18;

struct Edge {
    int u, v, w;
};

int parent[MAXN];
int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

int up[LOG][MAXN];
int min_w[LOG][MAXN];
int dep[MAXN];
vector<pair<int, int>> adj[MAXN];

void bfs(int root) {
    queue<int> q;
    q.push(root);
    dep[root] = 1;
    up[0][root] = 0;
    min_w[0][root] = 2000000000;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (v != up[0][u]) {
                up[0][v] = u;
                min_w[0][v] = w;
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
}

int query_min(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int res = 2000000000;
    int diff = dep[u] - dep[v];
    for (int k = 0; k < LOG; ++k) {
        if ((diff >> k) & 1) {
            res = min(res, min_w[k][u]);
            u = up[k][u];
        }
    }
    if (u == v) return res;
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[k][u] != up[k][v]) {
            res = min(res, min_w[k][u]);
            res = min(res, min_w[k][v]);
            u = up[k][u];
            v = up[k][v];
        }
    }
    res = min(res, min_w[0][u]);
    res = min(res, min_w[0][v]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            adj[i].clear();
            dep[i] = 0;
        }
        for (int i = 0; i < LOG; ++i) {
            for (int j = 0; j <= n; ++j) {
                up[i][j] = 0;
                min_w[i][j] = 2000000000;
            }
        }
        
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w > b.w;
        });
        
        long long W = 0;
        vector<bool> in_tree(m, false);
        for (int i = 0; i < m; ++i) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            int ru = find(u), rv = find(v);
            if (ru != rv) {
                parent[ru] = rv;
                W += w;
                in_tree[i] = true;
                adj[u].push_back({v, w});
                adj[v].push_back({u, w});
            }
        }
        
        bfs(1);
        
        for (int k = 1; k < LOG; ++k) {
            for (int i = 1; i <= n; ++i) {
                up[k][i] = up[k-1][up[k-1][i]];
                min_w[k][i] = min(min_w[k-1][i], min_w[k-1][up[k-1][i]]);
            }
        }
        
        long long ans = 0;
        for (int i = 0; i < m; ++i) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            if (in_tree[i]) {
                ans = max(ans, W + 4LL * w);
            } else {
                int min_edge = query_min(u, v);
                long long gain = 5LL * w - min_edge;
                if (gain > 0) {
                    ans = max(ans, W + gain);
                } else {
                    ans = max(ans, W);
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
