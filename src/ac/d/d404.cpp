#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int R, C;
int grid[105][105];
int dp[105][105];

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int solve(int r, int c) {
    if (dp[r][c] != -1) return dp[r][c];
    int res = 1;
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] < grid[r][c]) {
            res = max(res, 1 + solve(nr, nc));
        }
    }
    return dp[r][c] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            string S;
            cin >> S >> R >> C;
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    cin >> grid[i][j];
                    dp[i][j] = -1;
                }
            }
            
            int ans = 0;
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    ans = max(ans, solve(i, j));
                }
            }
            
            cout << S << ": " << ans << "\n";
        }
    }
    
    return 0;
}
