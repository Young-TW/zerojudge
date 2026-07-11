#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, Q;
    while (cin >> N >> M >> Q) {
        vector<pair<int, int>> edges(M);
        vector<vector<pair<int, int>>> adj(N);
        vector<bool> is_bridge(M, false);
        unordered_map<long long, int> edge_map;
        edge_map.reserve(M * 2);
        
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            edges[i] = {u, v};
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
            long long key = ((long long)min(u, v) << 32) | max(u, v);
            edge_map[key] = i;
        }
        
        // Bridge detection (Tarjan)
        vector<int> disc(N, 0), low(N, 0);
        vector<bool> visited(N, false);
        int timer = 0;
        function<void(int, int)> dfs_bridge = [&](int u, int parent_edge) {
            visited[u] = true;
            disc[u] = low[u] = ++timer;
            for (auto [v, eid] : adj[u]) {
                if (eid == parent_edge) continue;
                if (!visited[v]) {
                    dfs_bridge(v, eid);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > disc[u]) {
                        is_bridge[eid] = true;
                    }
                } else {
                    low[u] = min(low[u], disc[v]);
                }
            }
        };
        
        for (int i = 0; i < N; ++i) {
            if (!visited[i]) {
                dfs_bridge(i, -1);
            }
        }
        
        // 2-edge-connected components
        vector<int> comp_id(N, -1);
        vector<int> comp_size;
        int comp_cnt = 0;
        function<void(int)> dfs_comp = [&](int u) {
            comp_id[u] = comp_cnt;
            comp_size[comp_cnt]++;
            for (auto [v, eid] : adj[u]) {
                if (is_bridge[eid]) continue;
                if (comp_id[v] == -1) {
                    dfs_comp(v);
                }
            }
        };
        
        for (int i = 0; i < N; ++i) {
            if (comp_id[i] == -1) {
                comp_size.push_back(0);
                dfs_comp(i);
                comp_cnt++;
            }
        }
        
        // Bridge tree
        vector<vector<pair<int, int>>> tree(comp_cnt);
        for (int eid = 0; eid < M; ++eid) {
            if (is_bridge[eid]) {
                int u = edges[eid].first;
                int v = edges[eid].second;
                int c1 = comp_id[u];
                int c2 = comp_id[v];
                tree[c1].push_back({c2, eid});
                tree[c2].push_back({c1, eid});
            }
        }
        
        vector<int> tree_parent(comp_cnt, -1);
        vector<int> subtree_size(comp_cnt, 0);
        vector<int> tree_total(comp_cnt, 0);
        vector<int> bridge_child_comp(M, -1); // valid only for bridges
        
        function<void(int)> dfs_tree1 = [&](int u) {
            subtree_size[u] = comp_size[u];
            for (auto [v, eid] : tree[u]) {
                if (v == tree_parent[u]) continue;
                tree_parent[v] = u;
                dfs_tree1(v);
                subtree_size[u] += subtree_size[v];
                bridge_child_comp[eid] = v;
            }
        };
        
        function<void(int, int)> dfs_tree2 = [&](int u, int total) {
            tree_total[u] = total;
            for (auto [v, eid] : tree[u]) {
                if (v == tree_parent[u]) continue;
                dfs_tree2(v, total);
            }
        };
        
        for (int i = 0; i < comp_cnt; ++i) {
            if (tree_parent[i] == -1) {
                dfs_tree1(i);
                dfs_tree2(i, subtree_size[i]);
            }
        }
        
        // Answer queries
        for (int i = 0; i < Q; ++i) {
            int u, v;
            cin >> u >> v;
            long long key = ((long long)min(u, v) << 32) | max(u, v);
            int eid = edge_map[key];
            int ans;
            if (!is_bridge[eid]) {
                ans = tree_total[comp_id[u]];
            } else {
                int child = bridge_child_comp[eid];
                int c_u = comp_id[u];
                if (c_u == child) {
                    ans = subtree_size[child];
                } else {
                    ans = tree_total[c_u] - subtree_size[child];
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
