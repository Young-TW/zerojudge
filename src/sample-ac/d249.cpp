#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int dp[255][255];

int computeLCS(const string& s1, const string& s2, string& lcs_str, bool extract) {
    int n = s1.length();
    int m = s2.length();
    for (int i = 0; i <= n; ++i) dp[i][0] = 0;
    for (int j = 0; j <= m; ++j) dp[0][j] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    if (extract) {
        lcs_str.clear();
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (s1[i-1] == s2[j-1] && dp[i][j] == dp[i-1][j-1] + 1) {
                lcs_str += s1[i-1];
                i--;
                j--;
            } else if (dp[i-1][j] > dp[i][j-1]) {
                i--;
            } else {
                j--;
            }
        }
        reverse(lcs_str.begin(), lcs_str.end());
    }
    return dp[n][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2;
    while (cin >> s1 >> s2) {
        if (s1.empty() || s2.empty()) {
            cout << "no\n";
            continue;
        }
        int n = s1.length();
        int m = s2.length();
        int max_len = 0;
        int best_k = 0;
        string dummy;

        for (int k = 0; k < n; ++k) {
            string s1_rot = s1.substr(k) + s1.substr(0, k);
            int len = computeLCS(s1_rot, s2, dummy, false);
            if (len > max_len) {
                max_len = len;
                best_k = k;
            }
        }

        if (max_len == 0) {
            cout << "no\n";
        } else {
            string s1_rot = s1.substr(best_k) + s1.substr(0, best_k);
            string lcs_str;
            computeLCS(s1_rot, s2, lcs_str, true);
            cout << lcs_str << "\n";
            cout << fixed << setprecision(2) << (double)(max_len * 2) / (n + m) + 1e-9 << "\n";
        }
    }
    return 0;
}
