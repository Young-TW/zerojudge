#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    string S, T;
    while (cin >> K >> S >> T) {
        int n = S.size();
        int m = T.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (S[i-1] == T[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        vector<vector<int>> dp2(n + 1, vector<int>(m + 1, 0));
        int max_len = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (S[i-1] == T[j-1]) {
                    int low_i = max(1, i - K - 1);
                    int low_j = max(1, j - K - 1);
                    dp2[i][j] = dp2[low_i-1][low_j-1] + 1;
                    for (int x = low_i; x < i; ++x) {
                        for (int y = low_j; y < j; ++y) {
                            if (S[x-1] == T[y-1]) {
                                dp2[i][j] = max(dp2[i][j], dp2[x][y] + 1);
                            }
                        }
                    }
                    max_len = max(max_len, dp2[i][j]);
                }
            }
        }

        if (max_len == 0) {
            cout << dp[n][m] << '\n';
        } else {
            cout << max_len << '\n';
        }
    }

    return 0;
}
