#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int K;
    string S, T;
    while (cin >> K >> S >> T) {
        int n = (int)S.size();
        int m = (int)T.size();

        // dp[i][j] : subsequence ending at (i,j) (1‑based)
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        // R[i][j] : max of dp in rectangle rows [i-K .. i], cols [j-K .. j]
        vector<vector<int>> R(n + 1, vector<int>(m + 1, 0));

        // one deque per column for the vertical sliding maximum
        vector<deque<pair<int,int>>> colDeques(m + 1);
        int answer = 0;

        for (int i = 1; i <= n; ++i) {
            // ----- compute dp[i][*] using R[i-1][*] -----
            for (int j = 1; j <= m; ++j) {
                if (S[i-1] == T[j-1]) {
                    dp[i][j] = 1 + R[i-1][j-1];
                    if (dp[i][j] > answer) answer = dp[i][j];
                } else {
                    dp[i][j] = 0;
                }
            }

            // ----- vertical sliding maximum (height K+1) -----
            vector<int> vert(m + 1, 0);
            for (int j = 1; j <= m; ++j) {
                // insert current dp[i][j]
                while (!colDeques[j].empty() &&
                       colDeques[j].back().second <= dp[i][j])
                    colDeques[j].pop_back();
                colDeques[j].push_back({i, dp[i][j]});

                // erase rows that are out of the window
                while (!colDeques[j].empty() && colDeques[j].front().first < i - K)
                    colDeques[j].pop_front();

                vert[j] = colDeques[j].empty() ? 0 : colDeques[j].front().second;
            }

            // ----- horizontal sliding maximum (width K+1) -----
            deque<pair<int,int>> rowDeque;          // (column, value)
            for (int j = 1; j <= m; ++j) {
                while (!rowDeque.empty() && rowDeque.back().second <= vert[j])
                    rowDeque.pop_back();
                rowDeque.push_back({j, vert[j]});

                while (!rowDeque.empty() && rowDeque.front().first < j - K)
                    rowDeque.pop_front();

                R[i][j] = rowDeque.empty() ? 0 : rowDeque.front().second;
            }
        }

        cout << answer << '\n';
    }
    return 0;
}
