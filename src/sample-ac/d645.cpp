#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int i, c;
    while (cin >> i >> c) {
        vector<int> dp(c + 1, 0);
        
        for (int k = 0; k < i; ++k) {
            int v, w, t;
            cin >> v >> w >> t;
            
            if (t == -1) {
                // 完全背包
                for (int j = w; j <= c; ++j) {
                    if (dp[j - w] + v > dp[j]) {
                        dp[j] = dp[j - w] + v;
                    }
                }
            } else if (t == 1) {
                // 0-1背包
                for (int j = c; j >= w; --j) {
                    if (dp[j - w] + v > dp[j]) {
                        dp[j] = dp[j - w] + v;
                    }
                }
            } else {
                // 多重背包
                if (t * w >= c) {
                    // 數量足夠多，當作完全背包
                    for (int j = w; j <= c; ++j) {
                        if (dp[j - w] + v > dp[j]) {
                            dp[j] = dp[j - w] + v;
                        }
                    }
                } else {
                    // 二進制拆分
                    int remaining = t;
                    int power = 1;
                    while (remaining > 0) {
                        int count = min(power, remaining);
                        int current_v = v * count;
                        int current_w = w * count;
                        for (int j = c; j >= current_w; --j) {
                            if (dp[j - current_w] + current_v > dp[j]) {
                                dp[j] = dp[j - current_w] + current_v;
                            }
                        }
                        remaining -= count;
                        power <<= 1;
                    }
                }
            }
        }
        
        cout << dp[c] << "\n";
    }
    
    return 0;
}
