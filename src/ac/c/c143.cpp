#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        int t;
        cin >> t;
        vector<vector<bool>> grid(505, vector<bool>(505, false));
        
        for (int i = 0; i < t; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            
            int dx = x2 > x1 ? x2 - x1 : x1 - x2;
            int dy = y2 > y1 ? y2 - y1 : y1 - y2;
            int g = gcd(dx, dy);
            
            if (g == 0) {
                if (x1 >= 1 && x1 <= 504 && y1 >= 1 && y1 <= 504) {
                    grid[x1][y1] = true;
                }
                continue;
            }
            
            int sx = (x2 - x1) / g;
            int sy = (y2 - y1) / g;
            
            int x = x1, y = y1;
            for (int j = 0; j <= g; ++j) {
                if (x >= 1 && x <= 504 && y >= 1 && y <= 504) {
                    grid[x][y] = true;
                }
                x += sx;
                y += sy;
            }
        }
        
        int count = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (grid[i][j]) {
                    count++;
                }
            }
        }
        cout << count << "\n";
    }
    
    return 0;
}
