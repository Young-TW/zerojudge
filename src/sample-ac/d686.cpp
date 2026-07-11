#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int L;
    while (cin >> L && L) {
        int N;
        cin >> N;
        vector<int> C(N + 2);
        C[0] = 0;
        C[N + 1] = L;
        for (int i = 1; i <= N; ++i) {
            cin >> C[i];
        }
        
        vector<vector<int>> dp(N + 2, vector<int>(N + 2, 0));
        
        for (int len = 2; len <= N + 1; ++len) {
            for (int i = 0; i + len <= N + 1; ++i) {
                int j = i + len;
                dp[i][j] = 1000000000;
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
                dp[i][j] += C[j] - C[i];
            }
        }
        
        cout << "The minimum cutting is " << dp[0][N + 1] << ".\n";
    }
    
    return 0;
}
