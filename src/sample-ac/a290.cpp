#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> g(N + 1);
        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
        }
        int A, B;
        cin >> A >> B;

        vector<char> vis(N + 1, 0);
        queue<int> q;
        q.push(A);
        vis[A] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }

        cout << (vis[B] ? "Yes!!!" : "No!!!") << "\n";
    }
    return 0;
}
