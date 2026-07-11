#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int LOG = 20;

struct Query {
    int u, v, lca;
    long long dist;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    vector<long long> answers;

    while (cin >> n >> m) {
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            long long t;
            cin >> a >> b >> t;
            adj[a].emplace_back(b, t);
            adj[b].emplace_back(a, t);
        }

        vector<int> depth(n + 1);
        vector<long long> dist(n + 1);
        vector<long long> weight_to_parent(n + 1);
        vector<int> bfs_order;
        bfs_order.reserve(n);
        vector<vector<int>> parent(LOG, vector<int>(n + 1, 0));

        queue<int> q;
        q.push(1);
        depth[1] = 0;
        dist[1] = 0;
        parent[0][1] = 0;
        weight_to_parent[1] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            bfs_order.push_back(u);
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                long long w = edge.second;
                if (v == parent[0][u]) continue;
                parent[0][v] = u;
                depth[v] = depth[u] + 1;
                dist[v] = dist[u] + w;
                weight_to_parent[v] = w;
                q.push(v);
            }
        }

        for (int i = 1; i < LOG; i++) {
            for (int v = 1; v <= n; v++) {
                int p = parent[i - 1][v];
                parent[i][v] = p ? parent[i - 1][p] : 0;
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            int diff = depth[u] - depth[v];
            for (int i = 0; i < LOG; i++) {
                if (diff & (1 << i)) {
                    u = parent[i][u];
                }
            }
            if (u == v) return u;
            for (int i = LOG - 1; i >= 0; i--) {
                if (parent[i][u] != parent[i][v]) {
                    u = parent[i][u];
                    v = parent[i][v];
                }
            }
            return parent[0][u];
        };

        vector<Query> queries;
        queries.reserve(m);
        long long max_dist = 0;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            int l = lca(u, v);
            long long d = dist[u] + dist[v] - 2 * dist[l];
            queries.push_back({u, v, l, d});
            if (d > max_dist) max_dist = d;
        }

        auto check = [&](long long T) -> bool {
            vector<int> cnt(n + 1, 0);
            long long max_excess = 0;
            int total_long = 0;
            for (const auto& qry : queries) {
                if (qry.dist > T) {
                    total_long++;
                    long long excess = qry.dist - T;
                    if (excess > max_excess) max_excess = excess;
                    cnt[qry.u]++;
                    cnt[qry.v]++;
                    cnt[qry.lca] -= 2;
                }
            }
            if (total_long == 0) return true;

            for (int i = n - 1; i >= 0; i--) {
                int v = bfs_order[i];
                if (v == 1) continue;
                cnt[parent[0][v]] += cnt[v];
            }

            long long max_weight = 0;
            for (int v = 2; v <= n; v++) {
                if (cnt[v] == total_long) {
                    if (weight_to_parent[v] > max_weight) max_weight = weight_to_parent[v];
                }
            }
            return max_weight >= max_excess;
        };

        long long low = 0, high = max_dist;
        while (low < high) {
            long long mid = (low + high) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        answers.push_back(low);
    }

    for (size_t i = 0; i < answers.size(); i++) {
        if (i > 0) cout << '\n';
        cout << answers[i] << '\n';
    }

    return 0;
}
