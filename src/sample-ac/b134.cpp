#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<int> a(2 * N + 2);
        for (int i = 1; i <= N; ++i) {
            cin >> a[i];
            a[i + N] = a[i];
        }
        
        vector<vector<long long>> dp(2 * N + 2, vector<long long>(2 * N + 2, 0));
        
        for (int len = 2; len <= N; ++len) {
            for (int i = 1; i + len - 1 <= 2 * N - 1; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j] + (long long)a[i] * a[k+1] * a[j+1]);
                }
            }
        }
        
        long long ans = 0;
        for (int i = 1; i <= N; ++i) {
            ans = max(ans, dp[i][i + N - 1]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
