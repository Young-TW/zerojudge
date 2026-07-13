#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    string s1, s2;
    int L, K;
    while (getline(cin, s1)) {
        getline(cin, s2);
        cin >> L >> K;
        cin.ignore();

        int n = s1.size();
        int m = s2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX / 2));
        dp[0][0] = 0;

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (i == 0 && j == 0) continue;
                if (i > 0 && j > 0 && s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                if (i > 0) {
                    for (int len = 1; len <= L && i - len >= 0; ++len) {
                        dp[i][j] = min(dp[i][j], dp[i-len][j] + 1);
                    }
                }
                if (j > 0) {
                    for (int len = 1; len <= L && j - len >= 0; ++len) {
                        dp[i][j] = min(dp[i][j], dp[i][j-len] + 1);
                    }
                }
            }
        }

        if (dp[n][m] <= K) {
            cout << dp[n][m] << endl;
        } else {
            cout << "Impossible" << endl;
        }
    }
    return 0;
}
