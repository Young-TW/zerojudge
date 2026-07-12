#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        int k;
        cin >> k;
        vector<vector<int>> grid(n, vector<int>(n, 0));
        vector<vector<bool>> dead(n, vector<bool>(n, false));
        
        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;
            if (x >= 0 && x < n && y >= 0 && y < n) {
                if (!dead[y][x]) {
                    dead[y][x] = true;
                    for (int dy = -1; dy <= 1; ++dy) {
                        for (int dx = -1; dx <= 1; ++dx) {
                            if (dx == 0 && dy == 0) continue;
                            int nx = x + dx;
                            int ny = y + dy;
                            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                                if (!dead[ny][nx]) {
                                    grid[ny][nx]++;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            string row = "";
            for (int j = 0; j < n; ++j) {
                if (dead[i][j]) {
                    row += 'x';
                } else {
                    row += to_string(grid[i][j]);
                }
            }
            cout << row << "\n";
        }
        cout << "\n";
    }
    return 0;
}
