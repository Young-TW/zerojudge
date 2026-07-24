#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// 定義方向陣列，包含 8 個鄰居的相對座標 (dx, dy)
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int X, Y;
    // 處理多筆測資直到 EOF
    while (cin >> X >> Y) {
        int T;
        cin >> T;

        // 建立帶有邊界填充的棋盤
        // 實際有效區域為 [1..Y][1..X]，周圍一圈 [0] 和 [Y+1]/[X+1] 作為邊界（預設為 0）
        // 使用 vector<vector<int>> 動態配置，確保大小正確
        // 尺寸為 (Y + 2) 行，(X + 2) 列
        vector<vector<int>> grid(Y + 2, vector<int>(X + 2, 0));
        vector<vector<int>> next_grid(Y + 2, vector<int>(X + 2, 0));

        // 讀入初始狀態，填入有效區域
        for (int y = 1; y <= Y; ++y) {
            for (int x = 1; x <= X; ++x) {
                cin >> grid[y][x];
            }
        }

        // 模擬 T 個時間步驟
        for (int t = 0; t < T; ++t) {
            // 遍歷有效區域
            for (int y = 1; y <= Y; ++y) {
                for (int x = 1; x <= X; ++x) {
                    int neighbors = 0;
                    
                    // 統計 8 個鄰居的病毒數量
                    // 由於有 padding，這裡不需要檢查邊界，直接存取即可
                    // 邊界外的值永遠是 0
                    for (int dir = 0; dir < 8; ++dir) {
                        int nx = x + dx[dir];
                        int ny = y + dy[dir];
                        neighbors += grid[ny][nx];
                    }

                    int current = grid[y][x];

                    if (current == 1) {
                        // 規則 1: 有病毒，鄰居 2 或 3 個 -> 存活
                        if (neighbors == 2 || neighbors == 3) {
                            next_grid[y][x] = 1;
                        } else {
                            // 鄰居 < 2 或 > 3 -> 死亡
                            next_grid[y][x] = 0;
                        }
                    } else {
                        // 規則 2: 無病毒，鄰居正好 3 個 -> 繁殖
                        if (neighbors == 3) {
                            next_grid[y][x] = 1;
                        } else {
                            next_grid[y][x] = 0;
                        }
                    }
                }
            }

            // 將下一個狀態複製回當前狀態
            // 只複製有效區域即可，但為了簡單起見，整個交換或複製
            // 這裡選擇交換 vector 的內部指標以節省時間，但需注意邊界重置
            // 由於我們每次都會完整寫入 next_grid 的有效區域，且邊界永遠是 0
            // 直接 swap 是最快的，但 swap 後 next_grid 會變成舊的 grid
            // 舊的 grid 邊界也是 0，所以沒問題。
            swap(grid, next_grid);
        }

        // 輸出最終結果
        for (int y = 1; y <= Y; ++y) {
            for (int x = 1; x <= X; ++x) {
                cout << grid[y][x];
            }
            cout << "\n";
        }
    }

    return 0;
}
