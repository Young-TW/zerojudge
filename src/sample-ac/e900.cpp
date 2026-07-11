#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        int sumA = 0, sumB = 0;
        vector<int> deltas(N);
        for (int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            sumA += a;
            sumB += b;
            deltas[i] = b - a;
        }
        
        int diff = sumA - sumB;
        const int INF = 1e9;
        const int OFFSET = 12002;
        vector<int> dp(24005, INF);
        dp[OFFSET] = 0;
        
        for (int i = 0; i < N; ++i) {
            int d = deltas[i];
            if (d == 0) continue;
            if (d > 0) {
                for (int j = 24004; j >= d; --j) {
                    if (dp[j - d] != INF) {
                        if (dp[j - d] + 1 < dp[j]) {
                            dp[j] = dp[j - d] + 1;
                        }
                    }
                }
            } else {
                for (int j = 0; j <= 24004 + d; ++j) {
                    if (dp[j - d] != INF) {
                        if (dp[j - d] + 1 < dp[j]) {
                            dp[j] = dp[j - d] + 1;
                        }
                    }
                }
            }
        }
        
        int min_diff = abs(diff);
        int ans = 0;
        for (int i = 0; i <= 24004; ++i) {
            if (dp[i] != INF) {
                int sum_d = i - OFFSET;
                int current_diff = abs(diff + 2 * sum_d);
                if (current_diff < min_diff) {
                    min_diff = current_diff;
                    ans = dp[i];
                } else if (current_diff == min_diff) {
                    if (dp[i] < ans) {
                        ans = dp[i];
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
