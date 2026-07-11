#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        vector<vector<int>> adj(26, vector<int>(26, -1));
        for (int i = 0; i < 26; ++i) {
            adj[i][i] = 0;
        }

        for (int i = 0; i < N; ++i) {
            char u, v;
            int w;
            cin >> u >> v >> w;
            int u_idx = u - 'A';
            int v_idx = v - 'A';
            if (adj[u_idx][v_idx] == -1 || adj[u_idx][v_idx] > w) {
                adj[u_idx][v_idx] = w;
                adj[v_idx][u_idx] = w;
            }
        }

        char S, E;
        cin >> S >> E;
        int start = S - 'A';
        int end = E - 'A';

        vector<int> dist(26, INT_MAX);
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (int v = 0; v < 26; ++v) {
                if (adj[u][v] != -1) {
                    if (dist[u] + adj[u][v] < dist[v]) {
                        dist[v] = dist[u] + adj[u][v];
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        if (dist[end] == INT_MAX) {
            cout << "NoRoute\n";
        } else {
            cout << dist[end] << "\n";
        }
    }

    return 0;
}
