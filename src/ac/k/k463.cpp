#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> color(N + 1, 0);
        bool is_bipartite = true;
        int ans = 0;

        for (int i = 1; i <= N; ++i) {
            if (color[i] == 0) {
                queue<int> q;
                q.push(i);
                color[i] = 1;
                int cnt1 = 0, cnt2 = 0;

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();

                    if (color[u] == 1) cnt1++;
                    else cnt2++;

                    for (int v : adj[u]) {
                        if (color[v] == 0) {
                            color[v] = 3 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            is_bipartite = false;
                        }
                    }
                }
                ans += max(cnt1, cnt2);
            }
        }

        if (!is_bipartite) {
            cout << 0 << "\n";
        } else {
            cout << ans << "\n";
        }
    }
    return 0;
}
