#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N);
        vector<int> indegree(N, 0);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            indegree[v]++;
        }
        
        queue<int> q;
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        vector<long long> dp(N, 0);
        dp[0] = 1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                dp[v] += dp[u];
                if (--indegree[v] == 0) q.push(v);
            }
        }
        
        cout << dp[N-1] << "\n";
    }
    return 0;
}
