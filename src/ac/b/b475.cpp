#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d;
    while (cin >> d) {
        int n;
        if (!(cin >> n)) break;
        
        int grid[135][135] = {0};
        int sum[135][135] = {0};
        
        for (int i = 0; i < n; ++i) {
            int x, y, k;
            cin >> x >> y >> k;
            grid[x + 1][y + 1] += k;
        }
        
        for (int i = 1; i <= 129; ++i) {
            for (int j = 1; j <= 129; ++j) {
                sum[i][j] = grid[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
            }
        }
        
        int max_cnt = -1;
        int ans_cnt = 0;
        
        for (int i = 1; i <= 129; ++i) {
            for (int j = 1; j <= 129; ++j) {
                int x1 = max(1, i - d);
                int x2 = min(129, i + d);
                int y1 = max(1, j - d);
                int y2 = min(129, j + d);
                
                int cnt = sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
                
                if (cnt > max_cnt) {
                    max_cnt = cnt;
                    ans_cnt = 1;
                } else if (cnt == max_cnt) {
                    ans_cnt++;
                }
            }
        }
        
        cout << ans_cnt << " " << max_cnt << "\n";
    }
    
    return 0;
}
