#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<int> W(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> W[i];
        }
        
        const int MOD = 10007;
        long long total_sum = 0;
        long long max_ans = 0;
        
        for (int i = 1; i <= n; ++i) {
            long long sum_w = 0;
            long long sum_sq = 0;
            int m1 = 0, m2 = 0;
            
            for (int v : adj[i]) {
                int w = W[v];
                sum_w = (sum_w + w) % MOD;
                sum_sq = (sum_sq + (long long)w * w % MOD) % MOD;
                
                if (w > m1) {
                    m2 = m1;
                    m1 = w;
                } else if (w > m2) {
                    m2 = w;
                }
            }
            
            if (m2 > 0) {
                max_ans = max(max_ans, (long long)m1 * m2);
            }
            
            long long current_sum = (sum_w * sum_w % MOD - sum_sq + MOD) % MOD;
            total_sum = (total_sum + current_sum) % MOD;
        }
        
        cout << max_ans << " " << total_sum << "\n";
    }
    
    return 0;
}
