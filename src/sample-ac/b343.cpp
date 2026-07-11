#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n, m, l;
            cin >> n >> m >> l;
            
            vector<vector<int>> adj(n + 1);
            for (int i = 0; i < m; ++i) {
                int x, y;
                cin >> x >> y;
                adj[x].push_back(y);
            }
            
            vector<bool> visited(n + 1, false);
            int count = 0;
            queue<int> q;
            
            for (int i = 0; i < l; ++i) {
                int z;
                cin >> z;
                if (!visited[z]) {
                    visited[z] = true;
                    q.push(z);
                    while (!q.empty()) {
                        int u = q.front();
                        q.pop();
                        count++;
                        for (int v : adj[u]) {
                            if (!visited[v]) {
                                visited[v] = true;
                                q.push(v);
                            }
                        }
                    }
                }
            }
            cout << count << "\n";
        }
    }
    return 0;
}
