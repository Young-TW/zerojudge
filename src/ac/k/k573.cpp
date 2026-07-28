#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, K, Q;
    while (cin >> N >> M >> K >> Q) {
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<long long> antibody(N, 0);          // newest virus number known

        for (int ev = 0; ev < Q; ++ev) {
            int a;
            long long b;
            cin >> a >> b;

            vector<char> visited(N, 0);
            queue<pair<int,int>> q;                // (vertex, distance)
            q.emplace(a, 0);
            visited[a] = 1;

            int infected = 0;

            while (!q.empty()) {
                auto cur = q.front(); q.pop();
                int v = cur.first;
                int d = cur.second;

                if (antibody[v] < b) {
                    antibody[v] = b;
                    ++infected;

                    if (d == K) continue;          // depth limit reached
                    for (int nb : adj[v]) {
                        if (!visited[nb]) {
                            visited[nb] = 1;
                            q.emplace(nb, d + 1);
                        }
                    }
                }
                // else immune → do not expand
            }

            cout << infected << '\n';
        }
    }
    return 0;
}
