#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N;
        cin >> N;
        vector<int> w(N + 1);
        vector<vector<int>> adj(N + 1);
        vector<int> in_degree(N + 1, 0);
        
        for (int i = 1; i <= N; ++i) {
            int days, K;
            cin >> days >> K;
            w[i] = days;
            for (int j = 0; j < K; ++j) {
                int v;
                cin >> v;
                adj[i].push_back(v);
                in_degree[v]++;
            }
        }
        
        vector<int> dp(N + 1, 0);
        queue<int> q;
        
        for (int i = 1; i <= N; ++i) {
            if (in_degree[i] == 0) {
                dp[i] = w[i];
                q.push(i);
            }
        }
        
        int max_days = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            max_days = max(max_days, dp[u]);
            
            for (int v : adj[u]) {
                dp[v] = max(dp[v], dp[u] + w[v]);
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        cout << max_days << "\n";
    }
    
    return 0;
}
