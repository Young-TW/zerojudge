#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        vector<vector<int>> adj(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> adj[i][j];
            }
        }
        
        vector<bool> alive(n, true);
        vector<int> deg(n, 0), non(n, 0);
        queue<int> q;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && adj[i][j]) {
                    deg[i]++;
                }
            }
            non[i] = n - 1 - deg[i];
            if (deg[i] < 2 || non[i] < 2) {
                alive[i] = false;
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; ++v) {
                if (alive[v]) {
                    if (adj[u][v]) {
                        deg[v]--;
                    } else {
                        non[v]--;
                    }
                    if (deg[v] < 2 || non[v] < 2) {
                        alive[v] = false;
                        q.push(v);
                    }
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (alive[i]) {
                ans++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
