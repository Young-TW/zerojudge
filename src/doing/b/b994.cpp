#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> up;
    LCA(int n = 0) { init(n); }
    void init(int N) {
        n = N;
        LOG = 1;
        while ((1 << LOG) <= n) ++LOG;
        depth.assign(n + 1, 0);
        up.assign(LOG, vector<int>(n + 1, 0));
    }
    void dfs(int v, int p, const vector<vector<int>>& adj) {
        up[0][v] = p;
        for (int i = 1; i < LOG; ++i)
            up[i][v] = up[i - 1][up[i - 1][v]];
        for (int to : adj[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v, adj);
        }
    }
    void build(const vector<vector<int>>& adj, int root = 1) {
        depth[root] = 0;
        dfs(root, root, adj);
    }
    int kth_ancestor(int v, int k) const {
        for (int i = 0; i < LOG; ++i)
            if (k & (1 << i)) v = up[i][v];
        return v;
    }
    int lca(int a, int b) const {
        if (depth[a] < depth[b]) swap(a, b);
        a = kth_ancestor(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[i][a] != up[i][b]) {
                a = up[i][a];
                b = up[i][b];
            }
        }
        return up[0][a];
    }
    int dist(int a, int b) const {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    bool firstCase = true;
    while (cin >> n >> m) {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> W(n + 1);
        for (int i = 1; i <= n; ++i) cin >> W[i];
        vector<pair<int,int>> queries(m);
        for (int i = 0; i < m; ++i) cin >> queries[i].first >> queries[i].second;

        LCA lca(n);
        lca.build(adj, 1);

        vector<int> ans(n + 1, 0);
        vector<int> path;
        vector<int> rev;

        for (auto [S, T] : queries) {
            int L = lca.lca(S, T);
            path.clear();
            int cur = S;
            while (cur != L) {
                path.push_back(cur);
                cur = lca.up[0][cur];
            }
            path.push_back(L); // include LCA

            rev.clear();
            cur = T;
            while (cur != L) {
                rev.push_back(cur);
                cur = lca.up[0][cur];
            }
            for (int i = (int)rev.size() - 1; i >= 0; --i)
                path.push_back(rev[i]);

            for (int i = 0; i < (int)path.size(); ++i) {
                int node = path[i];
                if (W[node] == i) ++ans[node];
            }
        }

        if (!firstCase) cout << "\n";
        firstCase = false;
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << "\n";
    }
    return 0;
}
