#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<long long> h(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> h[i];
        }
        
        vector<int> order(N);
        for (int i = 0; i < N; ++i) {
            order[i] = i + 1;
        }
        sort(order.begin(), order.end(), [&](int a, int b) {
            return h[a] < h[b];
        });
        
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            if (h[u] < h[v]) {
                adj[u].push_back(v);
            } else if (h[u] > h[v]) {
                adj[v].push_back(u);
            }
        }
        
        vector<char> is_target(N + 1, 0);
        vector<unsigned int> dp(N + 1, 0);
        
        int Q;
        cin >> Q;
        while (Q--) {
            int D;
            cin >> D;
            fill(is_target.begin(), is_target.end(), 0);
            for (int i = 0; i < D; ++i) {
                int a;
                cin >> a;
                is_target[a] = 1;
            }
            
            fill(dp.begin(), dp.end(), 0);
            unsigned int max_dp = 0;
            
            for (int i = N - 1; i >= 0; --i) {
                int u = order[i];
                unsigned int best = 0;
                for (int v : adj[u]) {
                    if (dp[v] > best) {
                        best = dp[v];
                    }
                }
                int best_cnt = best >> 16;
                int best_len = best & 0xFFFF;
                dp[u] = ((unsigned int)(best_cnt + is_target[u]) << 16) | (unsigned int)(best_len + 1);
                
                if (dp[u] > max_dp) {
                    max_dp = dp[u];
                }
            }
            
            cout << (max_dp >> 16) << " " << (max_dp & 0xFFFF) << "\n";
        }
    }
    
    return 0;
}
