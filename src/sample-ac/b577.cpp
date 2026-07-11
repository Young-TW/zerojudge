#include <iostream>
#include <vector>
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
        vector<vector<pair<int, int>>> intervals_at_end(32768);
        for (int i = 0; i < N; ++i) {
            int S, E, C;
            cin >> S >> E >> C;
            intervals_at_end[E].push_back({S, C});
        }
        
        vector<int> dp(32768, 0);
        for (int t = 1; t <= 32767; ++t) {
            dp[t] = dp[t - 1];
            for (const auto& p : intervals_at_end[t]) {
                if (dp[p.first] + p.second > dp[t]) {
                    dp[t] = dp[p.first] + p.second;
                }
            }
        }
        
        cout << dp[32767] << "\n";
    }
    
    return 0;
}
