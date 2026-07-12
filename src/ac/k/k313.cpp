#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long M, K;
    while (cin >> N >> M >> K) {
        vector<long long> w(N), v(N);
        long long sum_W = 0, sum_V = 0;
        for (int i = 0; i < N; ++i) {
            cin >> w[i] >> v[i];
            sum_W += w[i];
            sum_V += v[i];
        }

        long long max_profit = 0;
        
        if (sum_W <= sum_V) {
            vector<long long> dp(sum_W + 1, -1);
            dp[0] = 0;
            long long current_max_W = 0;
            for (int i = 0; i < N; ++i) {
                current_max_W += w[i];
                for (long long j = current_max_W; j >= w[i]; --j) {
                    if (dp[j - w[i]] != -1) {
                        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
                    }
                }
            }
            for (long long j = 0; j <= sum_W; ++j) {
                if (dp[j] != -1) {
                    long long penalty = (j > M) ? (j - M) * K : 0;
                    long long profit = dp[j] - penalty;
                    if (profit > max_profit) {
                        max_profit = profit;
                    }
                }
            }
        } else {
            vector<long long> dp(sum_V + 1, 1e18);
            dp[0] = 0;
            long long current_max_V = 0;
            for (int i = 0; i < N; ++i) {
                current_max_V += v[i];
                for (long long j = current_max_V; j >= v[i]; --j) {
                    if (dp[j - v[i]] != 1e18) {
                        dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
                    }
                }
            }
            for (long long j = 0; j <= sum_V; ++j) {
                if (dp[j] != 1e18) {
                    long long penalty = (dp[j] > M) ? (dp[j] - M) * K : 0;
                    long long profit = j - penalty;
                    if (profit > max_profit) {
                        max_profit = profit;
                    }
                }
            }
        }

        cout << sum_V - max_profit << "\n";
    }

    return 0;
}
