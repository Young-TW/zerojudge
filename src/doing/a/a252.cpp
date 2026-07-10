#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string a, b, c;
    while (cin >> a >> b >> c) {
        int la = a.size(), lb = b.size(), lc = c.size();
        vector<vector<vector<int>>> dp(la + 1, vector<vector<int>>(lb + 1, vector<int>(lc + 1, 0)));
        for (int i = 1; i <= la; ++i) {
            for (int j = 1; j <= lb; ++j) {
                for (int k = 1; k <= lc; ++k) {
                    if (a[i-1] == b[j-1] && b[j-1] == c[k-1]) {
                        dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
                    } else {
                        dp[i][j][k] = max({dp[i-1][j][k], dp[i][j-1][k], dp[i][j][k-1]});
                    }
                }
            }
        }
        cout << dp[la][lb][lc] << "\n";
    }
    return 0;
}
