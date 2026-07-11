#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, m;
    while (cin >> N >> m) {
        vector<int> v(m + 1), p(m + 1), q(m + 1);
        vector<int> main_indices;
        vector<vector<int>> adj(m + 1);
        
        for (int i = 1; i <= m; ++i) {
            cin >> v[i] >> p[i] >> q[i];
            if (q[i] == 0) {
                main_indices.push_back(i);
            } else {
                adj[q[i]].push_back(i);
            }
        }
        
        vector<int> dp(N + 1, 0);
        
        for (int i : main_indices) {
            for (int j = N; j >= 0; --j) {
                // 只买主件
                if (j >= v[i]) {
                    dp[j] = max(dp[j], dp[j - v[i]] + v[i] * p[i]);
                }
                
                // 主件 + 附件1
                if (adj[i].size() >= 1) {
                    int idx1 = adj[i][0];
                    int cost = v[i] + v[idx1];
                    int val = v[i] * p[i] + v[idx1] * p[idx1];
                    if (j >= cost) {
                        dp[j] = max(dp[j], dp[j - cost] + val);
                    }
                }
                
                // 主件 + 附件2
                if (adj[i].size() >= 2) {
                    int idx2 = adj[i][1];
                    int cost = v[i] + v[idx2];
                    int val = v[i] * p[i] + v[idx2] * p[idx2];
                    if (j >= cost) {
                        dp[j] = max(dp[j], dp[j - cost] + val);
                    }
                }
                
                // 主件 + 附件1 + 附件2
                if (adj[i].size() >= 2) {
                    int idx1 = adj[i][0];
                    int idx2 = adj[i][1];
                    int cost = v[i] + v[idx1] + v[idx2];
                    int val = v[i] * p[i] + v[idx1] * p[idx1] + v[idx2] * p[idx2];
                    if (j >= cost) {
                        dp[j] = max(dp[j], dp[j - cost] + val);
                    }
                }
            }
        }
        
        cout << dp[N] << "\n";
    }
    
    return 0;
}
