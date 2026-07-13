#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s1, s2;
    if (!(cin >> s1 >> s2)) return 0;

    int n = (int)s1.length();
    int m = (int)s2.length();

    int k;
    if (!(cin >> k)) return 0;

    vector<int> results;
    results.reserve(k);

    // Allocate DP and Prefix Max tables once
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));

    for (int test = 0; test < k; ++test) {
        vector<int> gap(26, INF);
        string token;
        
        while (cin >> token) {
            if (token == "$") break;
            char ch = token[0];
            int val;
            cin >> val;
            gap[ch - 'A'] = val;
        }

        // Reset DP and Pref tables for current test case
        for (int i = 0; i <= n; ++i) {
            fill(dp[i].begin(), dp[i].begin() + m + 1, 0);
            fill(pref[i].begin(), pref[i].begin() + m + 1, 0);
        }

        int global_max = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i-1] == s2[j-1]) {
                    char c = s1[i-1];
                    int g = gap[c - 'A'];
                    
                    int best_prev = 0;
                    int r_end = i - 1;
                    int c_end = j - 1;
                    
                    if (r_end >= 1 && c_end >= 1) {
                        int r_start = (g == INF) ? 1 : max(1, r_end - g);
                        int c_start = (g == INF) ? 1 : max(1, c_end - g);
                        
                        if (r_start == 1 && c_start == 1) {
                            best_prev = pref[r_end][c_end];
                        } else {
                            for (int r = r_start; r <= r_end; ++r) {
                                for (int c = c_start; c <= c_end; ++c) {
                                    if (dp[r][c] > best_prev) {
                                        best_prev = dp[r][c];
                                    }
                                }
                            }
                        }
                    }
                    
                    dp[i][j] = best_prev + 1;
                    if (dp[i][j] > global_max) {
                        global_max = dp[i][j];
                    }
                }
                
                int val = dp[i][j];
                int up = pref[i-1][j];
                int left = pref[i][j-1];
                if (up > val) val = up;
                if (left > val) val = left;
                pref[i][j] = val;
            }
        }
        
        results.push_back(global_max);
    }

    for (int i = 0; i < (int)results.size(); ++i) {
        if (i > 0) cout << " ";
        cout << results[i];
    }
    cout << "\n";

    return 0;
}
