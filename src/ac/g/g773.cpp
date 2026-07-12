#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> adj(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int x;
                cin >> x;
                if (x) {
                    adj[i] |= (1 << j);
                }
            }
        }
        
        int size = 1 << N;
        vector<int> dp(size, 0);
        
        for (int mask = 1; mask < size; ++mask) {
            int lowbit = mask & (-mask);
            int v = __builtin_ctz(lowbit);
            int rest = mask ^ lowbit;
            dp[mask] = dp[rest];
            int next_mask = (mask & ~adj[v]) ^ lowbit;
            dp[mask] = max(dp[mask], dp[next_mask] + 1);
        }
        
        cout << dp[size - 1] << "\n";
    }
    return 0;
}
