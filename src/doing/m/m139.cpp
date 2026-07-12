#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, D;
    while (cin >> N >> K >> D) {
        vector<int> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }

        vector<vector<int>> dp(N + 1, vector<int>(D + 1, -1));
        dp[0][0] = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= D; ++j) {
                if (dp[i][j] == -1) continue;
                if (dp[i + 1][j] < dp[i][j]) {
                    dp[i + 1][j] = dp[i][j];
                }
                int cost = (i / K) + 1;
                if (j + cost <= D) {
                    int new_sum = dp[i][j] + a[i];
                    if (dp[i + 1][j + cost] < new_sum) {
                        dp[i + 1][j + cost] = new_sum;
                    }
                }
            }
        }

        int max_sum = 0;
        for (int j = 0; j <= D; ++j) {
            if (dp[N][j] > max_sum) {
                max_sum = dp[N][j];
            }
        }
        cout << max_sum << '\n';
    }

    return 0;
}
