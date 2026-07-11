#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    bool first_case = true;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int K;
        cin >> K;

        // Deduplicate edges (in case of duplicate pairs in input)
        for (int i = 1; i <= N; ++i) {
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        }

        vector<int> disc(N + 1, 0), low(N + 1, 0), parent(N + 1, -1), subtree_size(N + 1, 0);
        vector<bool> visited(N + 1, false);
        int timer = 0;
        int C_size = 0;

        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            disc[u] = low[u] = ++timer;
            subtree_size[u] = 1;
            ++C_size;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    parent[v] = u;
                    dfs(v);
                    subtree_size[u] += subtree_size[v];
                    low[u] = min(low[u], low[v]);
                } else if (v != parent[u]) {
                    low[u] = min(low[u], disc[v]);
                }
            }
        };

        dfs(K);

        if (!first_case) {
            cout << "\n";
        }
        first_case = false;

        if (C_size == 1) {
            cout << 0 << "\n";
            continue;
        }

        int min_hearers = C_size;
        int best_node = -1;

        for (int u = 1; u <= N; ++u) {
            if (u == K || !visited[u]) continue;
            int sum_separated = 0;
            for (int v : adj[u]) {
                if (parent[v] == u) { // v is a child in the DFS tree
                    if (low[v] >= disc[u]) {
                        sum_separated += subtree_size[v];
                    }
                }
            }
            int hearers = C_size - sum_separated;
            if (hearers < min_hearers) {
                min_hearers = hearers;
                best_node = u;
            } else if (hearers == min_hearers && hearers < C_size) {
                if (u < best_node) best_node = u;
            }
        }

        if (min_hearers == C_size) {
            cout << 0 << "\n";
        } else {
            cout << best_node << " " << min_hearers << "\n";
        }
    }
    return 0;
}
