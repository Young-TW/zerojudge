#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 20005;
const int MAX_M = 100005;
const int MAXLOG = 15;
const int INF = 2000000000;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};

struct TreeNode {
    int to, w;
};

Edge edges[MAX_M];
vector<TreeNode> adj[MAX_N];
int fa_dsu[MAX_N];
int dep[MAX_N];
int fa[MAX_N][MAXLOG + 1];
int mn[MAX_N][MAXLOG + 1];

int find(int x) {
    return fa_dsu[x] == x ? x : fa_dsu[x] = find(fa_dsu[x]);
}

void dfs(int u, int p) {
    for (const auto& edge : adj[u]) {
        int v = edge.to;
        int w = edge.w;
        if (v != p) {
            dep[v] = dep[u] + 1;
            fa[v][0] = u;
            mn[v][0] = w;
            dfs(v, u);
        }
    }
}

int query(int u, int v) {
    if (find(u) != find(v)) return -1;
    int res = INF;
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int j = 0; j <= MAXLOG; ++j) {
        if ((diff >> j) & 1) {
            res = min(res, mn[u][j]);
            u = fa[u][j];
        }
    }
    if (u == v) return res;
    for (int j = MAXLOG; j >= 0; --j) {
        if (fa[u][j] != fa[v][j]) {
            res = min(res, min(mn[u][j], mn[v][j]));
            u = fa[u][j];
            v = fa[v][j];
        }
    }
    res = min(res, min(mn[u][0], mn[v][0]));
    return res;
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; ++i) {
            fa_dsu[i] = i;
            adj[i].clear();
            dep[i] = 0;
            for (int j = 0; j <= MAXLOG; ++j) {
                fa[i][j] = 0;
                mn[i][j] = INF;
            }
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        }
        sort(edges, edges + m);
        for (int i = 0; i < m; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            int fu = find(u);
            int fv = find(v);
            if (fu != fv) {
                fa_dsu[fu] = fv;
                adj[u].push_back({v, w});
                adj[v].push_back({u, w});
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (dep[i] == 0) {
                dep[i] = 1;
                fa[i][0] = 0;
                mn[i][0] = INF;
                dfs(i, 0);
            }
        }
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                if (fa[i][j-1] != 0) {
                    fa[i][j] = fa[fa[i][j-1]][j-1];
                    mn[i][j] = min(mn[i][j-1], mn[fa[i][j-1]][j-1]);
                }
            }
        }
        int q;
        scanf("%d", &q);
        while (q--) {
            int u, v;
            scanf("%d %d", &u, &v);
            printf("%d\n", query(u, v));
        }
    }
    return 0;
}
