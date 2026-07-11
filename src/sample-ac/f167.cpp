#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N + 1);
        vector<int> in_deg(N + 1, 0);
        
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            in_deg[b]++;
        }
        
        queue<int> q;
        for (int i = 1; i <= N; ++i) {
            if (in_deg[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> res;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            res.push_back(u);
            
            for (int v : adj[u]) {
                in_deg[v]--;
                if (in_deg[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        if ((int)res.size() == N) {
            cout << "YES\n";
            for (int i = 0; i < N; ++i) {
                cout << res[i] << "\n";
            }
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
