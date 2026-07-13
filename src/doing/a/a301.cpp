#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <tuple>

using namespace std;

int N;
int board[5][7]; // x: 0-4, y: 0-6
int best_sol[10][3];
bool found = false;

// 複製棋盤
void copy_board(int src[5][7], int dst[5][7]) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 7; ++j)
            dst[i][j] = src[i][j];
}

// 檢查是否為空
bool check_empty(int b[5][7]) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 7; ++j)
            if (b[i][j] != 0) return false;
    return true;
}

// 消除邏輯，返回是否發生消除
bool eliminate(int b[5][7]) {
    bool to_clear[5][7];
    memset(to_clear, 0, sizeof(to_clear));
    bool has_clear = false;

    // 檢查橫向
    for (int y = 0; y < 7; ++y) {
        for (int x = 0; x < 3; ++x) {
            int c = b[x][y];
            if (c == 0) continue;
            if (b[x+1][y] == c && b[x+2][y] == c) {
                to_clear[x][y] = to_clear[x+1][y] = to_clear[x+2][y] = true;
                has_clear = true;
                // 繼續檢查更長的連續
                int k = x + 3;
                while (k < 5 && b[k][y] == c) {
                    to_clear[k][y] = true;
                    k++;
                }
            }
        }
    }

    // 檢查縱向
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            int c = b[x][y];
            if (c == 0) continue;
            if (b[x][y+1] == c && b[x][y+2] == c) {
                to_clear[x][y] = to_clear[x][y+1] = to_clear[x][y+2] = true;
                has_clear = true;
                int k = y + 3;
                while (k < 7 && b[x][k] == c) {
                    to_clear[x][k] = true;
                    k++;
                }
            }
        }
    }

    if (!has_clear) return false;

    // 執行消除
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 7; ++y) {
            if (to_clear[x][y]) b[x][y] = 0;
        }
    }
    return true;
}

// 重力掉落
void drop(int b[5][7]) {
    for (int x = 0; x < 5; ++x) {
        int write_y = 0;
        for (int read_y = 0; read_y < 7; ++read_y) {
            if (b[x][read_y] != 0) {
                b[x][write_y] = b[x][read_y];
                if (write_y != read_y) b[x][read_y] = 0;
                write_y++;
            }
        }
    }
}

// 處理消除和掉落的循環
void process_board(int b[5][7]) {
    while (true) {
        drop(b);
        if (!eliminate(b)) break;
    }
    drop(b); // 最後再掉一次確保緊湊
}

// DFS 搜索
// step: 當前步數
// path: 記錄路徑
void dfs(int step, vector<tuple<int, int, int>>& path) {
    if (found) return;

    if (check_empty(board)) {
        found = true;
        for (int i = 0; i < step; ++i) {
            best_sol[i][0] = get<0>(path[i]);
            best_sol[i][1] = get<1>(path[i]);
            best_sol[i][2] = get<2>(path[i]);
        }
        return;
    }

    if (step == N) return;

    // 嘗試所有可能的移動
    // 順序：x 從小到大，y 從小到大，方向先 1 (右) 後 -1 (左)
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 7; ++y) {
            if (board[x][y] == 0) continue;

            // 嘗試向右 (g=1)
            if (x < 4) {
                int old_board[5][7];
                copy_board(board, old_board);

                if (board[x+1][y] == 0) {
                    // 移動到空格，掉落
                    board[x][y] = 0;
                    board[x+1][y] = board[x+1][y]; // 原本就是 0
                    // 實際上要把方塊拿起來放到 x+1 列，然後讓它掉落
                    // 簡化：直接放到該列最下方可用的位置？
                    // 不，規則是：從原列抽出，從目標位置掉落。
                    // 因為目標位置 (x+1, y) 是空的，且下方必須也是空的（因為不能懸空，如果有方塊 y 不會是 0 除非上方也沒方塊）
                    // 等等，題目說：如果目標位置沒有方塊，被拖動的方块將從原豎列抽出，並從目標位置上掉落（直到不懸空）。
                    // 這裡 y 是當前方塊的高度。如果我們把 (x,y) 移到 (x+1, y)，但 (x+1, y) 是空的。
                    // 這意味著 (x+1, 0) 到 (x+1, y-1) 都是空的嗎？不一定。
                    // 規則是：它會掉落到 (x+1) 列的最低可用位置。
                    // 但題目描述是「沿橫向拖动某一方块一格」。
                    // 如果目標位置 (x+1, y) 沒有方塊，那麼方塊會從 (x,y) 移除，然後在 (x+1) 列從高處掉落。
                    // 由於我們是橫向移動一格，原本在 (x,y)，現在去 (x+1, y) 的位置開始掉。
                    // 其實結果就是：該方塊變成 (x+1) 列的一部分，並受重力影響落到底部。
                    // 讓我們模擬這個過程：
                    // 1. 取出顏色 c = board[x][y]
                    // 2. board[x][y] = 0
                    // 3. 將 c 放入 board[x+1] 的臨時緩衝，然後重新計算 board[x+1] 的堆疊。
                    // 簡單做法：先把 board[x][y] 設 0，然後把 c 加到 board[x+1] 的頂端（或對應位置），再跑 drop。
                    // 但要注意，drop 函數是處理整列的。
                    // 正確的模擬：
                    int c = board[x][y];
                    board[x][y] = 0;
                    // 暫時放在 (x+1, y) 或其他地方？
                    // 其實只要把 c 加到 x+1 列的非零序列中，然後跑 drop 就會自動排好。
                    // 但為了精確模擬「從目標位置掉落」，其實只要保證它進入該列，drop 會處理剩下的。
                    // 不過要注意，如果直接塞到最上面，drop 會讓它掉下來，結果是一樣的。
                    // 唯一差別是中間狀態？題目說掉落過程中不會消除，所以只要最終狀態對即可。
                    // 找到 x+1 列第一個 0 的位置（從下往上找第一個空的，或者直接加在現有堆疊上方）
                    int ny = 0;
                    while (ny < 7 && board[x+1][ny] != 0) ny++;
                    if (ny < 7) board[x+1][ny] = c;
                    
                    process_board(board);
                    path.push_back(make_tuple(x, y, 1));
                    dfs(step + 1, path);
                    path.pop_back();
                    if (found) return;
                    copy_board(old_board, board);
                } else {
                    // 交換
                    swap(board[x][y], board[x+1][y]);
                    process_board(board);
                    path.push_back(make_tuple(x, y, 1));
                    dfs(step + 1, path);
                    path.pop_back();
                    if (found) return;
                    copy_board(old_board, board);
                }
            }

            // 嘗試向左 (g=-1)
            if (x > 0) {
                int old_board[5][7];
                copy_board(board, old_board);

                if (board[x-1][y] == 0) {
                    int c = board[x][y];
                    board[x][y] = 0;
                    int ny = 0;
                    while (ny < 7 && board[x-1][ny] != 0) ny++;
                    if (ny < 7) board[x-1][ny] = c;

                    process_board(board);
                    path.push_back(make_tuple(x, y, -1));
                    dfs(step + 1, path);
                    path.pop_back();
                    if (found) return;
                    copy_board(old_board, board);
                } else {
                    swap(board[x][y], board[x-1][y]);
                    process_board(board);
                    path.push_back(make_tuple(x, y, -1));
                    dfs(step + 1, path);
                    path.pop_back();
                    if (found) return;
                    copy_board(old_board, board);
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    memset(board, 0, sizeof(board));
    
    // 輸入格式：5 行，每行代表一列 (x=0 到 4)，由下而上輸入，以 0 結束
    for (int x = 0; x < 5; ++x) {
        int y = 0;
        while (true) {
            int c;
            cin >> c;
            if (c == 0) break;
            board[x][y] = c;
            y++;
        }
    }

    vector<tuple<int, int, int>> path;
    found = false;
    dfs(0, path);

    if (found) {
        for (int i = 0; i < N; ++i) {
            cout << best_sol[i][0] << " " << best_sol[i][1] << " " << best_sol[i][2] << "\n";
        }
    } else {
        cout << "-1\n";
    }

    return 0;
}
