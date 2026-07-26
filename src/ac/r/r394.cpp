#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, Q;
    while (cin >> N >> M >> Q) {
        vector<pair<int,int>> edges(M);
        vector<vector<pair<int,int>>> adj(N);
        unordered_map<long long,int> id_of_edge;
        id_of_edge.reserve(M*2);
        for (int i = 0; i < M; ++i) {
            int u, v;  cin >> u >> v;
            edges[i] = {u, v};
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
            long long key = ( (long long)min(u,v) << 32 ) | (unsigned)max(u,v);
            id_of_edge[key] = i;
        }

        /* ---------- 1. bridges (Tarjan) ---------- */
        vector<int> disc(N, -1), low(N, 0);
        vector<char> is_bridge(M, 0);
        int timer = 0;
        function<void(int,int)> dfs_bridge = [&](int u, int parent_eid){
            disc[u] = low[u] = timer++;
            for (auto [v, eid] : adj[u]) {
                if (eid == parent_eid) continue;
                if (disc[v] == -1) {
                    dfs_bridge(v, eid);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > disc[u]) is_bridge[eid] = 1;
                } else {
                    low[u] = min(low[u], disc[v]);
                }
            }
        };
        for (int i = 0; i < N; ++i)
            if (disc[i] == -1) dfs_bridge(i, -1);

        /* ---------- 2. 2‑edge‑connected components ---------- */
        vector<int> comp(N, -1);
        vector<int> comp_size;
        int comp_cnt = 0;
        function<void(int)> dfs_comp = [&](int u){
            comp[u] = comp_cnt;
            ++comp_size[comp_cnt];
            for (auto [v, eid] : adj[u]) {
                if (is_bridge[eid]) continue;
                if (comp[v] == -1) dfs_comp(v);
            }
        };
        for (int i = 0; i < N; ++i) if (comp[i] == -1) {
            comp_size.push_back(0);
            dfs_comp(i);
            ++comp_cnt;
        }

        /* ---------- 3. bridge tree ---------- */
        vector<vector<pair<int,int>>> tree(comp_cnt);
        for (int eid = 0; eid < M; ++eid) if (is_bridge[eid]) {
            int a = edges[eid].first, b = edges[eid].second;
            int ca = comp[a], cb = comp[b];
            tree[ca].push_back({cb, eid});
            tree[cb].push_back({ca, eid});
        }

        /* ---------- 4. root tree, subtree sizes ---------- */
        int root = comp[0];
        vector<int> parent(comp_cnt, -1);
        vector<long long> sub(comp_cnt, 0);
        vector<int> child_of_bridge(M, -1);   // only valid for bridges
        function<void(int)> dfs_tree = [&](int u){
            sub[u] = comp_size[u];
            for (auto [v, eid] : tree[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                dfs_tree(v);
                sub[u] += sub[v];
                child_of_bridge[eid] = v;          // v is the deeper side
            }
        };
        dfs_tree(root);   // tree is connected because original graph is

        /* ---------- 5. answer queries ---------- */
        for (int i = 0; i < Q; ++i) {
            int u, v;  cin >> u >> v;
            long long key = ( (long long)min(u,v) << 32 ) | (unsigned)max(u,v);
            int eid = id_of_edge[key];
            if (!is_bridge[eid]) {
                cout << N << '\n';
            } else {
                int child = child_of_bridge[eid];
                long long ans = (long long)N - sub[child];
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
