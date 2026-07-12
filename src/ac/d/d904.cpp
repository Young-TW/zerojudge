#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C, N;
    while (cin >> C >> N) {
        vector<int> coins(N);
        for (int i = 0; i < N; ++i) {
            cin >> coins[i];
        }
        
        const int INF = 1e9;
        vector<int> dp(C + 1, INF);
        dp[0] = 0;
        
        for (int i = 1; i <= C; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i >= coins[j] && dp[i - coins[j]] != INF) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        
        cout << dp[C] << "\n";
    }
    
    return 0;
}
