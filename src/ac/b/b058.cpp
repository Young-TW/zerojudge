#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        int m;
        cin >> m;
        vector<int> W(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> W[i];
        }

        vector<vector<int>> adj(n + 1);
        vector<vector<int>> radj(n + 1);
        vector<int> indeg(n + 1, 0);
        vector<int> outdeg(n + 1, 0);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            radj[v].push_back(u);
            indeg[v]++;
            outdeg[u]++;
        }

        vector<int> F(n + 1, 0);
        queue<int> q;

        for (int i = 1; i <= n; ++i) {
            if (indeg[i] == 0) {
                F[i] = W[i];
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (F[v] < F[u] + W[v]) {
                    F[v] = F[u] + W[v];
                }
                if (--indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        int T = 0;
        for (int i = 1; i <= n; ++i) {
            if (F[i] > T) {
                T = F[i];
            }
        }

        vector<int> L(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (outdeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : radj[u]) {
                if (L[v] < W[u] + L[u]) {
                    L[v] = W[u] + L[u];
                }
                if (--outdeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (F[i] == T - L[i]) {
                ans++;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
