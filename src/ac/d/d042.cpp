#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long dp[2][66][2][2];
    long long ans[66][66];
    
    for (int n = 1; n <= 65; n++) {
        for (int s = 0; s <= 65; s++) {
            ans[n][s] = 0;
        }
    }

    for (int n = 1; n <= 65; n++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int t = 0; t < 2; t++) {
                        dp[i][j][k][t] = 0;
                    }
                }
            }
        }

        dp[0][0][0][0] = 1;

        for (int i = 0; i < n; i++) {
            int cur = i % 2;
            int nxt = (i + 1) % 2;
            
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int t = 0; t < 2; t++) {
                        long long ways = dp[cur][j][k][t];
                        if (ways == 0) continue;
                        
                        // 1. Next drawer is Unlocked (U)
                        dp[nxt][j][0][0] += ways;
                        
                        // 2. Next drawer is Locked (L)
                        bool is_safe = (i == 0) || (k == 1);
                        int new_t = is_safe ? 1 : 0;
                        dp[nxt][j + new_t][1][new_t] += ways;
                    }
                }
            }
            
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int t = 0; t < 2; t++) {
                        dp[cur][j][k][t] = 0;
                    }
                }
            }
        }

        int final_state = n % 2;
        for (int s = 0; s <= n; s++) {
            ans[n][s] = dp[final_state][s][0][0] + dp[final_state][s][0][1] + 
                        dp[final_state][s][1][0] + dp[final_state][s][1][1];
        }
    }

    int n, s;
    while (cin >> n >> s) {
        if (n < 0 && s < 0) break;
        cout << ans[n][s] << "\n";
    }

    return 0;
}
