#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<int>> grid(11, vector<int>(11));
    
    // 讀取 11x11 網格
    while (cin >> grid[0][0]) {
        for (int i = 0; i < 11; ++i) {
            for (int j = (i == 0 ? 1 : 0); j < 11; ++j) {
                cin >> grid[i][j];
            }
        }

        // 初始化軌跡記錄
        vector<vector<bool>> visited(11, vector<bool>(11, false));
        vector<pair<int, int>> path;

        int x, y;
        while (cin >> x >> y && (x != -1 || y != -1)) {
            int cx = x;
            int cy = y;
            
            // 如果起點已經走過，直接停止（根據題目邏輯：已經流過的則停止）
            if (visited[cy][cx]) {
                continue;
            }

            visited[cy][cx] = true;
            path.push_back({cx, cy});

            while (true) {
                int nx = -1;
                int ny = -1;
                int min_h = grid[cy][cx];
                bool found = false;

                // 檢查周圍 8 個方向
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (dx == 0 && dy == 0) continue;

                        int tx = cx + dx;
                        int ty = cy + dy;

                        // 檢查邊界
                        if (tx >= 0 && tx < 11 && ty >= 0 && ty < 11) {
                            // 條件：更低的高度 且 尚未流過
                            if (grid[ty][tx] < min_h && !visited[ty][tx]) {
                                min_h = grid[ty][tx];
                                nx = tx;
                                ny = ty;
                                found = true;
                            }
                        }
                    }
                }

                if (found) {
                    cx = nx;
                    cy = ny;
                    visited[cy][cx] = true;
                    path.push_back({cx, cy});
                } else {
                    break;
                }
            }
        }

        // 輸出結果
        vector<string> output(11, string(11, '.'));
        for (const auto& p : path) {
            output[p.second][p.first] = '*';
        }

        for (int i = 0; i < 11; ++i) {
            cout << output[i] << "\n";
        }
    }

    return 0;
}
