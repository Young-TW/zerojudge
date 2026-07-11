#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

bool grid[505][505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        memset(grid, 0, sizeof(grid));
        int px = 0, py = 0;
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            grid[x][y] = true;
            if (i > 0) {
                if (x == px) {
                    int y1 = min(y, py);
                    int y2 = max(y, py);
                    for (int j = y1; j <= y2; ++j) {
                        grid[x][j] = true;
                    }
                } else {
                    int x1 = min(x, px);
                    int x2 = max(x, px);
                    for (int j = x1; j <= x2; ++j) {
                        grid[j][y] = true;
                    }
                }
            }
            px = x;
            py = y;
        }
        
        string border(n + 2, '-');
        cout << border << "\n";
        for (int i = 1; i <= n; ++i) {
            cout << "|";
            for (int j = 1; j <= n; ++j) {
                cout << (grid[i][j] ? "*" : " ");
            }
            cout << "|\n";
        }
        cout << border << "\n";
    }
    
    return 0;
}
