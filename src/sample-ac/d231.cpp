#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s1, s2;
    while (cin >> s1 >> s2) {
        int n = s1.length();
        int m = s2.length();
        int dp[55][55] = {0};
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        string lcs = "";
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (s1[i-1] == s2[j-1]) {
                lcs += s1[i-1];
                i--;
                j--;
            } else if (dp[i-1][j] > dp[i][j-1]) {
                i--;
            } else {
                j--;
            }
        }
        
        reverse(lcs.begin(), lcs.end());
        
        if (lcs.empty()) {
            cout << "E\n";
        } else {
            cout << lcs << "\n";
        }
    }
    
    return 0;
}
