#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    while (cin >> m) {
        vector<string> adj(m);
        for (int i = 0; i < m; ++i) {
            cin >> adj[i];
        }
        int start, end, N;
        cin >> start >> end >> N;
        
        start--;
        end--;
        
        vector<long long> dp(m, 0);
        dp[start] = 1;
        
        long long ans = 0;
        for (int step = 1; step <= N; ++step) {
            vector<long long> next_dp(m, 0);
            for (int u = 0; u < m; ++u) {
                if (dp[u] == 0) continue;
                for (int v = 0; v < m; ++v) {
                    if (adj[u][v] == '1') {
                        next_dp[v] += dp[u];
                    }
                }
            }
            dp = next_dp;
            ans += dp[end];
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
