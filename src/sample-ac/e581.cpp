#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int w, h;
    while (cin >> w >> h && (w || h)) {
        int n;
        cin >> n;
        bool wolf[105][105];
        memset(wolf, false, sizeof(wolf));
        
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            if (x <= 100 && y <= 100) {
                wolf[x][y] = true;
            }
        }
        
        unsigned long long dp[105][105];
        memset(dp, 0, sizeof(dp));
        
        dp[0][0] = 1;
        
        for (int i = 0; i <= w; ++i) {
            for (int j = 0; j <= h; ++j) {
                if (wolf[i][j]) {
                    dp[i][j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) continue;
                if (i > 0) dp[i][j] += dp[i-1][j];
                if (j > 0) dp[i][j] += dp[i][j-1];
            }
        }
        
        if (dp[w][h] == 0) {
            cout << "There is no path.\n";
        } else if (dp[w][h] == 1) {
            cout << "There is one path from Little Red Riding Hood's house to her grandmother's house.\n";
        } else {
            cout << "There are " << dp[w][h] << " paths from Little Red Riding Hood's house to her grandmother's house.\n";
        }
    }
    
    return 0;
}
