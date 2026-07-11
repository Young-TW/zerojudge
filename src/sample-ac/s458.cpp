#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int A;
        cin >> A;
        vector<int> start_nodes(A);
        for (int i = 0; i < A; ++i) {
            cin >> start_nodes[i];
        }

        vector<int> dist(N, -1);
        queue<int> q;

        for (int node : start_nodes) {
            if (dist[node] == -1) {
                dist[node] = 0;
                q.push(node);
            }
        }

        int max_dist = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    if (dist[v] > max_dist) {
                        max_dist = dist[v];
                    }
                    q.push(v);
                }
            }
        }

        cout << max_dist << "\n";
    }

    return 0;
}
