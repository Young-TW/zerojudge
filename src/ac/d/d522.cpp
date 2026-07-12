#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    while (cin >> n >> k) {
        vector<vector<int>> grid(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        
        vector<pair<int, int>> cells;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cells.push_back({i, j});
            }
        }
        
        sort(cells.begin(), cells.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
            return grid[a.first][a.second] < grid[b.first][b.second];
        });
        
        const long long INF = 1e18;
        vector<vector<long long>> dp(n, vector<long long>(n, -INF));
        dp[0][0] = grid[0][0];
        
        for (auto& cell : cells) {
            int i = cell.first;
            int j = cell.second;
            if (dp[i][j] == -INF) continue;
            
            for (int y = max(0, j - k); y <= min(n - 1, j + k); ++y) {
                if (y != j && grid[i][y] > grid[i][j]) {
                    dp[i][y] = max(dp[i][y], dp[i][j] + grid[i][y]);
                }
            }
            for (int x = max(0, i - k); x <= min(n - 1, i + k); ++x) {
                if (x != i && grid[x][j] > grid[i][j]) {
                    dp[x][j] = max(dp[x][j], dp[i][j] + grid[x][j]);
                }
            }
        }
        
        long long ans = -INF;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans = max(ans, dp[i][j]);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
