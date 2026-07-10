#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<vector<int>> adj(101);
        for (int i = 0; i < k; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
        }
        vector<char> vis(101, 0);
        queue<int> q;
        q.push(0);
        vis[0] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        cout << (vis[n] ? "Ok!" : "Impossib1e!") << "\n";
    }
    return 0;
}
