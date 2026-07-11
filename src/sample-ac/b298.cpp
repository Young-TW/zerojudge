#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, L, Q;
    while (cin >> N >> M >> L >> Q) {
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
        }

        vector<bool> visited(N + 1, false);
        queue<int> q;

        for (int i = 0; i < L; ++i) {
            int x;
            cin >> x;
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        for (int i = 0; i < Q; ++i) {
            int y;
            cin >> y;
            if (visited[y]) {
                cout << "TUIHUOOOOOO\n";
            } else {
                cout << "YA~~\n";
            }
        }
    }

    return 0;
}
