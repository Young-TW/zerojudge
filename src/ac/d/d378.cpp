#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    int case_num = 1;
    while (cin >> N >> M) {
        vector<vector<int>> grid(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }
        
        vector<vector<int>> dp(N, vector<int>(M, 0));
        dp[0][0] = grid[0][0];
        
        for (int i = 1; i < N; ++i) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        
        for (int j = 1; j < M; ++j) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j < M; ++j) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        
        cout << "Case #" << case_num << " :\n";
        cout << dp[N-1][M-1] << "\n";
        case_num++;
    }
    
    return 0;
}
