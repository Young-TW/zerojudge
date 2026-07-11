#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n, m, o;
    while (cin >> n >> m >> o) {
        vector<pair<int, int>> jobs(o);
        for (int i = 0; i < o; ++i) {
            cin >> jobs[i].first >> jobs[i].second;
        }

        vector<vector<int>> dp(o + 1, vector<int>(n + 1, -1));
        dp[0][0] = 0;

        for (int i = 1; i <= o; ++i) {
            int time = jobs[i-1].first;
            int score = jobs[i-1].second;
            for (int j = 0; j <= n; ++j) {
                dp[i][j] = dp[i-1][j];
                if (j >= time && dp[i-1][j-time] != -1) {
                    if (dp[i][j] < dp[i-1][j-time] + score) {
                        dp[i][j] = dp[i-1][j-time] + score;
                    }
                }
            }
        }

        int min_time = INT_MAX;
        int max_score = 0;
        for (int j = 0; j <= n; ++j) {
            for (int i = 0; i <= o; ++i) {
                if (dp[i][j] >= m) {
                    if (j < min_time || (j == min_time && dp[i][j] > max_score)) {
                        min_time = j;
                        max_score = dp[i][j];
                    }
                }
            }
        }

        if (min_time == INT_MAX) {
            cout << "0 0" << endl;
        } else {
            cout << min_time << " " << max_score << endl;
        }
    }
    return 0;
}
