#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int LOG = 16;  // 2^15 = 32768 > 32767

    int N;
    while (cin >> N) {
        vector<vector<int>> adj(N + 1);
        vector<int> in_deg(N + 1, 0), out_deg(N + 1, 0);

        for (int i = 1; i <= N; ++i) {
            int x;
            while (cin >> x) {
                if (x == 0) break;
                adj[i].push_back(x);
                ++out_deg[i];
                ++in_deg[x];
            }
        }

        vector<int> sources, sinks;
        for (int i = 1; i <= N; ++i) {
            if (in_deg[i] == 0) sources.push_back(i);
            if (out_deg[i] == 0) sinks.push_back(i);
        }

        // Build reversed graph G_rev (nodes 0..N, 0 is super-source)
        vector<vector<int>> G_rev(N + 1);
        for (int u = 1; u <= N; ++u) {
            for (int v : adj[u]) {
                G_rev[v].push_back(u);  // original u->v becomes v->u in G_rev
            }
        }
        for (int t : sinks) {
            G_rev[0].push_back(t);  // super-source to each sink
        }

        // Topological sort of G_rev (Kahn's algorithm)
        vector<int> in_deg_rev(N + 1, 0);
        for (int u = 0; u <= N; ++u) {
            for (int v : G_rev[u]) ++in_deg_rev[v];
        }

        vector<int> topo;
        topo.reserve(N + 1);
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int v : G_rev[u]) {
                if (--in_deg_rev[v] == 0) q.push(v);
            }
        }

        // Dominator tree construction
        vector<array<int, LOG>> up(N + 1);
        vector<int> idom(N + 1, -1);
        vector<int> depth(N + 1, 0);

        idom[0] = 0;
        depth[0] = 0;
        for (int k = 0; k < LOG; ++k) up[0][k] = 0;

        // LCA helper (captures up, depth, LOG by reference)
        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            int diff = depth[u] - depth[v];
            for (int k = 0; k < LOG; ++k) {
                if (diff & (1 << k)) u = up[u][k];
            }
            if (u == v) return u;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[u][k] != up[v][k]) {
                    u = up[u][k];
                    v = up[v][k];
                }
            }
            return up[u][0];
        };

        // Process nodes in topological order (skip super-source 0)
        for (size_t idx = 1; idx < topo.size(); ++idx) {
            int v = topo[idx];
            int lca_node;

            if (out_deg[v] == 0) {  // sink in original graph
                lca_node = 0;
            } else {
                lca_node = adj[v][0];
                for (size_t i = 1; i < adj[v].size(); ++i) {
                    lca_node = lca(lca_node, adj[v][i]);
                }
            }

            idom[v] = lca_node;
            depth[v] = depth[lca_node] + 1;
            up[v][0] = lca_node;
            for (int k = 1; k < LOG; ++k) {
                up[v][k] = up[up[v][k - 1]][k - 1];
            }
        }

        // Count original sources in each subtree of the dominator tree
        vector<int> cnt(N + 1, 0);
        for (int s : sources) cnt[s] = 1;

        // Propagate counts bottom-up (reverse topological order)
        for (int idx = (int)topo.size() - 1; idx >= 1; --idx) {
            int v = topo[idx];
            int p = idom[v];
            if (p != v) cnt[p] += cnt[v];
        }

        int num_locations = 0;
        int max_blocked = 0;
        for (int v = 1; v <= N; ++v) {
            if (in_deg[v] == 0) continue;   // source (nest)
            if (out_deg[v] == 0) continue;  // sink (fortress)
            if (cnt[v] > 0) {
                ++num_locations;
                if (cnt[v] > max_blocked) max_blocked = cnt[v];
            }
        }

        cout << num_locations << ' ' << max_blocked << '\n';
    }
    return 0;
}
