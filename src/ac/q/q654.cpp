#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> rev_adj(N);
        vector<int> out_degree(N, 0);

        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            rev_adj[v].push_back(u);
            out_degree[u]++;
        }

        queue<int> q;
        for (int i = 0; i < N; ++i) {
            if (out_degree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : rev_adj[u]) {
                out_degree[v]--;
                if (out_degree[v] == 0) {
                    q.push(v);
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < N; ++i) {
            if (out_degree[i] > 0) {
                ans.push_back(i);
            }
        }

        if (ans.empty()) {
            cout << -1 << "\n";
        } else {
            for (int i = 0; i < ans.size(); ++i) {
                if (i > 0) cout << " ";
                cout << ans[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
