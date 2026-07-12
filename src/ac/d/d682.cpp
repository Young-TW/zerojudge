#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, N, P;
    bool first = true;
    while (cin >> M >> N >> P) {
        if (!first) {
            cout << "\n";
        }
        first = false;
        
        int dp[10001];
        memset(dp, 0, sizeof(dp));
        
        for (int i = 0; i < N; ++i) {
            int costs[50], powers[50];
            for (int j = 0; j < P; ++j) {
                cin >> costs[j] >> powers[j];
            }
            for (int j = M; j >= 0; --j) {
                for (int k = 0; k < P; ++k) {
                    if (j >= costs[k]) {
                        if (dp[j - costs[k]] + powers[k] > dp[j]) {
                            dp[j] = dp[j - costs[k]] + powers[k];
                        }
                    }
                }
            }
        }
        
        int ans = 0;
        for (int j = 0; j <= M; ++j) {
            if (dp[j] > ans) {
                ans = dp[j];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
