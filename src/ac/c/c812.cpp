#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Vk;
    long long q;
    while (cin >> N >> Vk >> q) {
        vector<vector<pair<int, long long>>> adj(N + 1);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<bool> visited(N + 1, false);
        queue<int> bfs_queue;
        bfs_queue.push(Vk);
        visited[Vk] = true;
        int count = 0;

        while (!bfs_queue.empty()) {
            int u = bfs_queue.front();
            bfs_queue.pop();

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                long long w = edge.second;
                if (!visited[v] && w >= q) {
                    visited[v] = true;
                    count++;
                    bfs_queue.push(v);
                }
            }
        }

        cout << count << "\n";
    }

    return 0;
}
