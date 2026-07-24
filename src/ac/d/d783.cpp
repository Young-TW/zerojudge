#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

// 定義座標結構
struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 全局變數定義棒子與網格的關係
// 網格點 (x, y), 0<=x<=3, 0<=y<=3? 不，題目是 3x3 格子，座標是格點還是格子中心？
// 題目描述：左下角網格是原點 (0,0)? 不，"左下角的網格是原點 (0,0)" 這句話有點歧義。
// 通常 3x3 格子，座標可能是指格子的索引 (1~9) 或者是頂點座標。
// 看範例：棒子座標 "2 0 2 1" 和 "2 1 3 1"。
// 如果是格子索引 1-9，那座標應該是 (row, col)。
// 但棒子座標給的是四個整數，像是 (x1, y1, x2, y2)。
// 讓我們仔細解讀："左下角的網格是原點 (0,0)" -> 這可能指格子的座標系統。
// 但棒子是畫在格子之間的線。
// 假設格子座標為 (x, y) 其中 x in [0, 2], y in [0, 2]。
// 格子編號 1-9 如何對應？
// 通常順序是：
// 7 8 9
// 4 5 6
// 1 2 3
// 或者
// 1 2 3
// 4 5 6
// 7 8 9
// 看範例輸入 1: S=1, C=2. 棒子 "1 1 1 0"。
// 如果 1 和 2 相鄰，棒子在它們之間。
// 假設編號方式是：
// 1 2 3
// 4 5 6
// 7 8 9
// 那麼 1 是 (0,0), 2 是 (1,0), 3 是 (2,0)... ? 或者 y 軸向上？
// 題目說 "左下角的網格是原點 (0,0)"。若 1 在左下，則 1=(0,0), 2=(1,0), 3=(2,0), 4=(0,1)...
// 這樣 1 和 2 之間的棒子應該是 x=1, y 從 0 到 1? 或是水平線？
// 棒子 "1 1 1 0" 連接 (1,1) 和 (1,0)。這是一條垂直線 x=1, y 從 0 到 1。
// 如果格子 1 是 (0,0)，格子 2 是 (1,0)。它們之間的邊界是 x=1, y in [0,1]。
// 這符合 "1 1 1 0" (x=1, y=1 到 x=1, y=0)。
// 所以格子座標 (gx, gy) 對應編號：id = gx + gy * 3 + 1。
// 其中 gx in [0, 2], gy in [0, 2]。
// 1: (0,0), 2: (1,0), 3: (2,0)
// 4: (0,1), 5: (1,1), 6: (2,1)
// 7: (0,2), 8: (1,2), 9: (2,2)
// 棒子連接兩個相鄰格子。
// 垂直棒子：分隔 (x, y) 和 (x+1, y)。座標為 (x+1, y) 到 (x+1, y+1)。
// 水平棒子：分隔 (x, y) 和 (x, y+1)。座標為 (x, y+1) 到 (x+1, y+1)。
// 讓我們驗證一下：
// 格子 1 (0,0) 和 2 (1,0) 之間的垂直棒子：x=1, y 從 0 到 1。端點 (1,0) 和 (1,1)。
// 輸入範例 1: "1 1 1 0" -> (1,1) 到 (1,0)。正確。
// 格子 1 (0,0) 和 4 (0,1) 之間的水平棒子：y=1, x 從 0 到 1。端點 (0,1) 和 (1,1)。
// 總共 12 根棒子：
// 垂直：x=1 (y=0,1,2), x=2 (y=0,1,2), x=3 (y=0,1,2)? 
// 網格寬度 3，所以垂直線有 x=1, x=2, x=3? 
// 格子 x 範圍 0,1,2。右邊界是 x=3。
// 垂直棒子位於 x=1, 2, 3。每列 3 根？不，格子高度 3，所以 y 方向有 3 段。
// 垂直棒子：
// x=1: (1,0)-(1,1), (1,1)-(1,2), (1,2)-(1,3) -> 3 根
// x=2: (2,0)-(2,1), (2,1)-(2,2), (2,2)-(2,3) -> 3 根
// x=3: (3,0)-(3,1), (3,1)-(3,2), (3,2)-(3,3) -> 3 根
// 共 9 根垂直？不對，3x3 格子，內部垂直線是 x=1, x=2。邊界呢？
// 題目圖示顯示棒子是在格子之間。通常邊界不算，或者題目給的座標範圍限制了棒子。
// 題目說 "12 支棒子"。
// 3x3 網格，內部垂直線：x=1 (3段), x=2 (3段) -> 6 根。
// 內部水平線：y=1 (3段), y=2 (3段) -> 6 根。
// 總共 12 根。這符合題目。
// 所以座標範圍：
// 垂直棒子 x in {1, 2}, y in {0, 1, 2} (連接 (x, y) 和 (x, y+1))
// 水平棒子 y in {1, 2}, x in {0, 1, 2} (連接 (x, y) 和 (x+1, y))
// 讓我們給每根棒子編號 0-11。
// 規則：
// 垂直棒子 (x, y) 到 (x, y+1):
//   x=1, y=0 -> ID 0 (分隔 (0,0) 和 (1,0))
//   x=1, y=1 -> ID 1 (分隔 (0,1) 和 (1,1))
//   x=1, y=2 -> ID 2 (分隔 (0,2) 和 (1,2))
//   x=2, y=0 -> ID 3 (分隔 (1,0) 和 (2,0))
//   x=2, y=1 -> ID 4 (分隔 (1,1) 和 (2,1))
//   x=2, y=2 -> ID 5 (分隔 (1,2) 和 (2,2))
// 水平棒子 (x, y) 到 (x+1, y):
//   y=1, x=0 -> ID 6 (分隔 (0,0) 和 (0,1))
//   y=1, x=1 -> ID 7 (分隔 (1,0) 和 (1,1))
//   y=1, x=2 -> ID 8 (分隔 (2,0) 和 (2,1))
//   y=2, x=0 -> ID 9 (分隔 (0,1) 和 (0,2))
//   y=2, x=1 -> ID 10 (分隔 (1,1) 和 (1,2))
//   y=2, x=2 -> ID 11 (分隔 (2,1) 和 (2,2))

// 輔助函數：將格子編號轉為 (gx, gy)
void get_grid_pos(int id, int &gx, int &gy) {
    id--; // 0-based
    gx = id % 3;
    gy = id / 3;
}

// 輔助函數：給定兩個端點，找出棒子 ID
// 輸入座標可能無序 (x1,y1,x2,y2) 或 (x2,y2,x1,y1)
int get_stick_id(int x1, int y1, int x2, int y2) {
    // 確保 x1 <= x2, y1 <= y2 以便比較？不，直接判斷方向
    if (x1 == x2) {
        // 垂直棒子
        int x = x1;
        int y_min = min(y1, y2);
        // x 必須是 1 或 2
        if (x < 1 || x > 2) return -1;
        if (y_min < 0 || y_min > 2) return -1;
        // ID 計算: (x-1)*3 + y_min
        return (x - 1) * 3 + y_min;
    } else if (y1 == y2) {
        // 水平棒子
        int y = y1;
        int x_min = min(x1, x2);
        // y 必須是 1 或 2
        if (y < 1 || y > 2) return -1;
        if (x_min < 0 || x_min > 2) return -1;
        // ID 計算: 6 + (y-1)*3 + x_min
        return 6 + (y - 1) * 3 + x_min;
    }
    return -1;
}

// 檢查在給定的棒子遮罩下，start 和 end 是否連通
// mask 中 bit i 為 1 表示棒子 i 存在（阻擋），為 0 表示已移除（可通行）
bool is_connected(int start_id, int end_id, int mask) {
    if (start_id == end_id) return true;
    
    int sx, sy, ex, ey;
    get_grid_pos(start_id, sx, sy);
    get_grid_pos(end_id, ex, ey);
    
    bool visited[3][3];
    memset(visited, 0, sizeof(visited));
    
    queue<pair<int, int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        
        if (cur.first == ex && cur.second == ey) return true;
        
        for (int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3 && !visited[nx][ny]) {
                // 檢查中間的棒子
                int stick_id = -1;
                if (dx[i] == 1) { 
                    // 向右移動: (x, y) -> (x+1, y). 垂直棒子 x=x+1, y=y
                    // 棒子座標 (x+1, y) 到 (x+1, y+1)
                    // x+1 必須是 1 或 2. 
                    // 若 cur.x=0, nx=1 -> x=1. OK.
                    // 若 cur.x=1, nx=2 -> x=2. OK.
                    // 若 cur.x=2, nx=3 -> 越界，不會進來。
                    stick_id = get_stick_id(cur.first + 1, cur.second, cur.first + 1, cur.second + 1);
                } else if (dx[i] == -1) {
                    // 向左移動: (x, y) -> (x-1, y). 垂直棒子 x=x, y=y
                    stick_id = get_stick_id(cur.first, cur.second, cur.first, cur.second + 1);
                } else if (dy[i] == 1) {
                    // 向上移動: (x, y) -> (x, y+1). 水平棒子 y=y+1, x=x
                    stick_id = get_stick_id(cur.first, cur.second + 1, cur.first + 1, cur.second + 1);
                } else if (dy[i] == -1) {
                    // 向下移動: (x, y) -> (x, y-1). 水平棒子 y=y, x=x
                    stick_id = get_stick_id(cur.first, cur.second, cur.first + 1, cur.second);
                }
                
                if (stick_id != -1) {
                    // 如果棒子存在 (mask 中 bit 為 1)，則不能通過
                    if ((mask >> stick_id) & 1) {
                        continue;
                    }
                }
                
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    
    return false;
}

// 記憶化陣列: -1 未知, 0 必敗, 1 必勝
int memo[1 << 12];
int target_S, target_C;

// 遞迴函數：當前玩家是否能贏
// mask: 當前存在的棒子集合
bool can_win(int mask) {
    if (memo[mask] != -1) {
        return memo[mask] == 1;
    }
    
    // 嘗試移除每一根存在的棒子
    bool can_force_win = false;
    for (int i = 0; i < 12; i++) {
        if ((mask >> i) & 1) {
            int next_mask = mask ^ (1 << i);
            // 檢查移除後是否連通
            if (is_connected(target_S, target_C, next_mask)) {
                // 移除這根棒子後連通了，當前玩家立即獲勝
                can_force_win = true;
                break;
            } else {
                // 未連通，輪到對手
                // 如果對手在 next_mask 狀態下必敗，則當前玩家必勝
                if (!can_win(next_mask)) {
                    can_force_win = true;
                    break;
                }
            }
        }
    }
    
    memo[mask] = can_force_win ? 1 : 0;
    return can_force_win;
}

void solve() {
    int T;
    if (!(cin >> T)) return;
    
    for (int case_num = 1; case_num <= T; case_num++) {
        int S, C, R;
        cin >> S >> C >> R;
        
        int initial_mask = (1 << 12) - 1; // 初始所有 12 根棒子都存在
        
        for (int i = 0; i < R; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int id = get_stick_id(x1, y1, x2, y2);
            if (id != -1) {
                initial_mask &= ~(1 << id);
            }
        }
        
        // 檢查初始狀態
        if (is_connected(S, C, initial_mask)) {
            cout << "Case " << case_num << ": No Cheese!" << endl;
        } else {
            // 初始化 memo
            memset(memo, -1, sizeof(memo));
            target_S = S;
            target_C = C;
            
            if (can_win(initial_mask)) {
                cout << "Case " << case_num << ": SOHA" << endl;
            } else {
                cout << "Case " << case_num << ": TARA" << endl;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
