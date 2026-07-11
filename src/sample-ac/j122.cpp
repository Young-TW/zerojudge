#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        vector<string> grid(N);
        int wr = -1, wc = -1;
        
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 'W') {
                    wr = i;
                    wc = j;
                }
            }
        }
        
        vector<vector<int>> dp(N, vector<int>(N, 0));
        
        for (int c = 0; c < N; ++c) {
            if (grid[0][c] != 'B') {
                dp[0][c] = 1;
            }
        }
        
        for (int r = 1; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (grid[r][c] == 'B') {
                    dp[r][c] = 0;
                    continue;
                }
                
                long long ways = 0;
                
                if (c - 1 >= 0) {
                    if (grid[r - 1][c - 1] != 'B') {
                        ways += dp[r - 1][c - 1];
                    } else if (r - 2 >= 0 && c - 2 >= 0 && grid[r - 2][c - 2] != 'B') {
                        ways += dp[r - 2][c - 2];
                    }
                }
                
                if (c + 1 < N) {
                    if (grid[r - 1][c + 1] != 'B') {
                        ways += dp[r - 1][c + 1];
                    } else if (r - 2 >= 0 && c + 2 < N && grid[r - 2][c + 2] != 'B') {
                        ways += dp[r - 2][c + 2];
                    }
                }
                
                dp[r][c] = ways % MOD;
            }
        }
        
        cout << "Case " << t << ": " << dp[wr][wc] << "\n";
    }
    
    return 0;
}
