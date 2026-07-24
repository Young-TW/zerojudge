#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // 定義八個方向加上中心點 (雖然中心點是數字本身，不需要檢查，但為了迴圈方便可以統一定義偏移量)
    // 實際上我們只需要檢查周圍 8 格
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // 儲存需要插旗的位置 (row, col)
    // 使用雙緩衝區概念：先記錄所有要改變的位置，最後再統一修改
    // 避免在掃描過程中修改地圖，導致後續數字判斷時將新插的旗子 ('P') 誤判為已知的安全區或地雷
    // 題目要求：統計的是「未翻開的格子 (#)」數量。如果中途把 # 改成 P，可能會影響後面數字的統計邏輯嗎？
    // 題目描述：「如果有數字週圍九宮格中未翻開的格子數量 (含已插旗格子數量) = 數字本身」
    // 這裡的「已插旗格子數量」指的是輸入時就已經是旗子嗎？不，輸入只有 #, _, 數字。
    // 題意解讀關鍵：題目說「未翻開的格子數量 (含已插旗格子數量)」。
    // 但在本題輸入中，沒有預先存在的旗子。所有的旗子都是我們要插的。
    // 關鍵在於：判斷條件是基於「原始狀態」還是「即時狀態」？
    // 根據範例與常見 Minesweeper 邏輯，這通常是單輪推導：
    // 對於每個數字，計算其周圍目前標記為 '#' 的格子總數。如果這個總數 == 數字值，則這些 '#' 全部都是地雷。
    // 如果在掃描過程中，前面的數字已经把某些 '#' 變成了 'P'，那麼後面的數字在計算「未翻開格子 (#)」時，數量就會變少，導致判斷失敗。
    // 因此，必須基於「原始地圖」來進行所有判斷，最後再統一輸出結果。這就是雙緩衝區/延遲更新的意義。

    vector<pair<int, int>> flags_to_place;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = grid[i][j];
            // 只處理數字格
            if (c >= '1' && c <= '8') {
                int mine_count = c - '0';
                int unknown_count = 0;
                
                // 統計周圍 '#' 的數量
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    // 檢查邊界
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                        if (grid[ni][nj] == '#') {
                            unknown_count++;
                        }
                    }
                }

                // 如果周圍未翻開格子數等於數字本身，則這些格子都是地雷
                if (unknown_count == mine_count && unknown_count > 0) {
                    // 記錄下這些位置準備插旗
                    for (int k = 0; k < 8; ++k) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            if (grid[ni][nj] == '#') {
                                flags_to_place.push_back({ni, nj});
                            }
                        }
                    }
                }
            }
        }
    }

    // 統一應用插旗動作
    for (const auto& pos : flags_to_place) {
        grid[pos.first][pos.second] = 'P';
    }

    // 輸出結果
    for (int i = 0; i < n; ++i) {
        cout << grid[i] << "\n";
    }

    return 0;
}
