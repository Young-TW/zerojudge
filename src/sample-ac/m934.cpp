#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> a(n + 1);
        vector<int> pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }
        
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int len = 2; len <= n; ++len) {
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                int min_cost = -1;
                for (int k = l; k < r; ++k) {
                    int sum_l = pref[k] - pref[l - 1];
                    int sum_r = pref[r] - pref[k];
                    int cost = dp[l][k] + dp[k + 1][r] + abs(sum_l - sum_r);
                    if (min_cost == -1 || cost < min_cost) {
                        min_cost = cost;
                    }
                }
                dp[l][r] = min_cost;
            }
        }
        
        cout << dp[1][n] << "\n";
    }
    
    return 0;
}
