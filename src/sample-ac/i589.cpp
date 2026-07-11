#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    while (cin >> n >> m >> q) {
        // Special case: n = 1 (though constraints imply n >= 2, handle for safety)
        if (n == 1) {
            for (int i = 0; i < m; ++i) { int a, b; cin >> a >> b; }
            for (int i = 0; i < q; ++i) { int a, b, c; cin >> a >> b >> c; cout << "NO\n"; }
            continue;
        }

        vector<vector<pair<int,int>>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int a, b; cin >> a >> b;
            adj[a].emplace_back(b, i);
            adj[b].emplace_back(a, i);
        }

        // Tarjan's algorithm for articulation points and biconnected components
        vector<int> disc(n + 1, 0), low(n + 1, 0);
        vector<bool> is_articulation(n + 1, false);
        vector<pair<int,int>> stk;
        vector<vector<int>> components;
        int timer = 0;

        auto dfs = [&](auto&& self, int u, int parent_edge) -> void {
            disc[u] = low[u] = ++timer;
            int children = 0;
            for (auto [v, eid] : adj[u]) {
                if (eid == parent_edge) continue;
                if (!disc[v]) {
                    stk.emplace_back(u, v);
                    children++;
                    self(self, v, eid);
                    low[u] = min(low[u], low[v]);
                    if (low[v] >= disc[u]) {
                        if (parent_edge != -1 || children > 1) {
                            is_articulation[u] = true;
                        }
                        components.emplace_back();
                        int cid = components.size() - 1;
                        while (true) {
                            auto e = stk.back(); stk.pop_back();
                            components[cid].push_back(e.first);
                            components[cid].push_back(e.second);
                            if (e.first == u && e.second == v) break;
                        }
                    }
                } else if (disc[v] < disc[u]) {
                    stk.emplace_back(u, v);
                    low[u] = min(low[u], disc[v]);
                }
            }
        };
        dfs(dfs, 1, -1);

        // Pop any remaining edges (should not occur for a connected graph)
        if (!stk.empty()) {
            components.emplace_back();
            int cid = components.size() - 1;
            while (!stk.empty()) {
                auto e = stk.back(); stk.pop_back();
                components[cid].push_back(e.first);
                components[cid].push_back(e.second);
            }
        }

        // Check if there is any articulation point
        bool any_articulation = false;
        for (int v = 1; v <= n; ++v) {
            if (is_articulation[v]) { any_articulation = true; break; }
        }

        // If no articulation points, every query with distinct a,b,c is YES
        if (!any_articulation) {
            for (int i = 0; i < q; ++i) {
                int a, b, c; cin >> a >> b >> c;
                if (a == c || b == c) cout << "NO\n";
                else if (a == b) cout << "YES\n";
                else cout << "YES\n";
            }
            continue;
        }

        // Build block-cut tree
        vector<int> node_id(n + 1, 0);
        for (int v = 1; v <= n; ++v) {
            if (is_articulation[v]) node_id[v] = v;
        }
        int num_blocks = components.size();
        int max_node = n + num_blocks;
        vector<vector<int>> tree(max_node + 1);
        vector<int> last_seen(n + 1, 0);
        int mark = 0;

        for (int i = 0; i < num_blocks; ++i) {
            int bid = n + 1 + i;
            mark++;
            for (int v : components[i]) {
                if (last_seen[v] == mark) continue;
                last_seen[v] = mark;
                if (is_articulation[v]) {
                    tree[bid].push_back(v);
                    tree[v].push_back(bid);
                } else {
                    node_id[v] = bid;
                }
            }
        }

        // LCA preprocessing on the block-cut tree
        vector<int> depth(max_node + 1, 0);
        vector<array<int, LOG>> parent(max_node + 1);
        for (int i = 1; i <= max_node; ++i) parent[i].fill(0);

        int root = 1;
        while (root <= max_node && tree[root].empty()) root++;
        // The tree is connected and has edges (since there are articulation points), so root is valid.

        vector<int> stack;
        stack.push_back(root);
        parent[root][0] = 0;
        depth[root] = 0;
        while (!stack.empty()) {
            int u = stack.back(); stack.pop_back();
            for (int v : tree[u]) {
                if (v == parent[u][0]) continue;
                parent[v][0] = u;
                depth[v] = depth[u] + 1;
                stack.push_back(v);
            }
        }

        for (int k = 1; k < LOG; ++k) {
            for (int i = 1; i <= max_node; ++i) {
                int p = parent[i][k-1];
                parent[i][k] = p ? parent[p][k-1] : 0;
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            int diff = depth[u] - depth[v];
            for (int k = 0; k < LOG; ++k) {
                if (diff & (1 << k)) u = parent[u][k];
            }
            if (u == v) return u;
            for (int k = LOG - 1; k >= 0; --k) {
                if (parent[u][k] != parent[v][k]) {
                    u = parent[u][k];
                    v = parent[v][k];
                }
            }
            return parent[u][0];
        };

        auto dist = [&](int u, int v) {
            int w = lca(u, v);
            return depth[u] + depth[v] - 2 * depth[w];
        };

        // Answer queries
        for (int i = 0; i < q; ++i) {
            int a, b, c; cin >> a >> b >> c;
            if (a == c || b == c) {
                cout << "NO\n";
            } else if (a == b) {
                cout << "YES\n";
            } else if (!is_articulation[c]) {
                cout << "YES\n";
            } else {
                int u = node_id[a];
                int v = node_id[b];
                int w = c; // c is an articulation point, its node_id is itself
                if (dist(u, v) == dist(u, w) + dist(w, v)) {
                    cout << "NO\n";
                } else {
                    cout << "YES\n";
                }
            }
        }
    }
    return 0;
}
