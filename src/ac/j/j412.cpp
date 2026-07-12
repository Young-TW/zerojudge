#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

bool black[1005][1005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int h, w, n;
    while (cin >> h >> w >> n) {
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                black[i][j] = false;
            }
        }
        
        for (int i = 0; i < n; ++i) {
            int r, c;
            cin >> r >> c;
            if (r >= 1 && r <= h && c >= 1 && c <= w) {
                black[r][c] = true;
            }
        }
        
        if (black[1][1] || black[h][w]) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<long long> dp(w + 1, 0);
        dp[1] = 1;
        
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                if (i == 1 && j == 1) continue;
                if (black[i][j]) {
                    dp[j] = 0;
                } else {
                    dp[j] = dp[j] + dp[j - 1];
                }
            }
        }
        
        cout << dp[w] << "\n";
    }
    
    return 0;
}
