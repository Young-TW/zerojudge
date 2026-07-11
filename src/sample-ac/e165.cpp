#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n >> k;
            if (k > n) k = n;
            
            vector<long long> x(n);
            for (int i = 0; i < n; ++i) {
                cin >> x[i];
            }
            sort(x.begin(), x.end());
            
            vector<long long> prefix(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                prefix[i + 1] = prefix[i] + x[i];
            }
            
            vector<vector<long long>> cost(n, vector<long long>(n, 0));
            for (int l = 0; l < n; ++l) {
                for (int r = l; r < n; ++r) {
                    int mid = l + (r - l) / 2;
                    long long left_cnt = mid - l;
                    long long right_cnt = r - mid;
                    long long left_sum = prefix[mid] - prefix[l];
                    long long right_sum = prefix[r + 1] - prefix[mid + 1];
                    cost[l][r] = x[mid] * left_cnt - left_sum + right_sum - x[mid] * right_cnt;
                }
            }
            
            vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, LLONG_MAX / 2));
            dp[0][0] = 0;
            for (int i = 1; i <= n; ++i) {
                dp[i][1] = cost[0][i - 1];
                for (int j = 2; j <= k; ++j) {
                    for (int m = j; m <= i; ++m) {
                        dp[i][j] = min(dp[i][j], dp[m - 1][j - 1] + cost[m - 1][i - 1]);
                    }
                }
            }
            
            cout << dp[n][k] << "\n";
        }
    }
    return 0;
}
