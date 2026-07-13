#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<int> books(K);
        for (int i = 0; i < K; ++i) {
            cin >> books[i];
        }

        set<pair<int, int>> edges;
        vector<vector<int>> adj(N);
        vector<int> in_degree(N, 0);

        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            if (edges.insert({u, v}).second) {
                adj[u].push_back(v);
                in_degree[v]++;
            }
        }

        vector<bool> unlocked(N, false);
        queue<int> q;

        for (int i = 0; i < K; ++i) {
            int book = books[i];
            if (!unlocked[book]) {
                unlocked[book] = true;
                q.push(book);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0 && !unlocked[v]) {
                    unlocked[v] = true;
                    q.push(v);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (unlocked[i]) {
                ans++;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
