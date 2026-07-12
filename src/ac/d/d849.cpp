#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, X, Y;
    while (cin >> n >> m >> X >> Y) {
        unsigned long long dp[25][25] = {0};
        bool blocked[25][25] = {false};
        
        int dx[] = {0, -2, -2, -1, -1, 1, 1, 2, 2};
        int dy[] = {0, -1, 1, -2, 2, -2, 2, -1, 1};
        
        for (int i = 0; i < 9; ++i) {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if (nx >= 0 && nx <= 20 && ny >= 0 && ny <= 20) {
                blocked[nx][ny] = true;
            }
        }
        
        if (!blocked[0][0]) {
            dp[0][0] = 1;
        }
        
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (blocked[i][j]) {
                    dp[i][j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) continue;
                if (i > 0) dp[i][j] += dp[i-1][j];
                if (j > 0) dp[i][j] += dp[i][j-1];
            }
        }
        
        cout << dp[n][m] << "\n";
    }
    
    return 0;
}
