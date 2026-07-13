#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    while (cin >> N >> K) {
        vector<int> prices(N);
        for (int i = 0; i < N; ++i) {
            cin >> prices[i];
        }

        if (K == 0 || N < 2) {
            cout << 0 << '\n';
            continue;
        }

        K = min(K, N / 2);

        vector<vector<int>> dp(K + 1, vector<int>(N, 0));

        for (int k = 1; k <= K; ++k) {
            int max_diff = -prices[0];
            for (int i = 1; i < N; ++i) {
                dp[k][i] = max(dp[k][i - 1], prices[i] + max_diff);
                max_diff = max(max_diff, dp[k - 1][i] - prices[i]);
            }
        }

        cout << dp[K][N - 1] << '\n';
    }

    return 0;
}
