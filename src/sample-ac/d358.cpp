#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> adj(n + 1);
        vector<int> in_degree(n + 1, 0);
        vector<int> val(n + 1, 100);
        
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            adj[b].push_back(a);
            in_degree[a]++;
        }
        
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }
        
        int count = 0;
        long long total = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            count++;
            total += val[u];
            
            for (int v : adj[u]) {
                if (val[v] < val[u] + 1) {
                    val[v] = val[u] + 1;
                }
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        if (count < n) {
            cout << "Poor Xed\n";
        } else {
            cout << total << "\n";
        }
    }
    
    return 0;
}
