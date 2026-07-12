#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int w = 21;
    int h = 15;
    vector<string> grid(h);
    
    // 讀取地圖
    for (int i = 0; i < h; ++i) {
        if (!(cin >> grid[i])) return 0;
    }

    // 尋找蛇的初始位置 's'
    int head_x = 0, head_y = 0;
    bool found = false;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (grid[y][x] == 's') {
                head_x = x;
                head_y = y;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    // 蛇的身體，使用 deque 儲存座標，front 是頭，back 是尾
    deque<pair<int, int>> snake;
    snake.push_back({head_x, head_y});
    
    // 將起始點標記為空格，因為蛇已經在那裡了，後續判斷碰撞用
    grid[head_y][head_x] = 'o';

    char dir;
    int steps;

    // 讀取指令直到 EOF
    while (cin >> dir >> steps) {
        int dx = 0, dy = 0;
        if (dir == 'N') dy = -1;
        else if (dir == 'S') dy = 1;
        else if (dir == 'W') dx = -1;
        else if (dir == 'E') dx = 1;

        for (int i = 0; i < steps; ++i) {
            int next_x = head_x + dx;
            int next_y = head_y + dy;

            // 處理穿牆邏輯 (Wrap around)
            if (next_x < 0) next_x = w - 1;
            if (next_x >= w) next_x = 0;
            if (next_y < 0) next_y = h - 1;
            if (next_y >= h) next_y = 0;

            // 檢查碰撞
            bool collision = false;

            // 1. 檢查障礙物 'x'
            if (grid[next_y][next_x] == 'x') {
                collision = true;
            }
            // 2. 檢查自己的身體
            // 注意：如果下一步是吃到食物，尾巴不會移動，所以整個身體都在碰撞檢測範圍內
            // 如果下一步沒吃到食物，尾巴會移動，所以目前的尾巴位置下一秒會是空的，不算碰撞
            // 但為了簡化，我們先檢查該位置是否為蛇身。
            // 由於我們沒有即時更新 grid 來反映蛇身移動（只靠 deque 追蹤），我們需要遍歷 deque
            // 例外：如果下一步沒吃食物，當前的 tail 在下一步會移開，所以撞到尾不算撞（除非蛇長度為 1 且原地打轉，但這題方向改變不會原地打轉）
            
            // 更精確的邏輯：
            // 計算是否吃食物
            bool eat_food = (grid[next_y][next_x] == '$');
            
            // 檢查是否撞到身體
            // 如果沒吃食物，尾巴會縮進，所以 deque.back() 的位置下一秒是安全的
            // 如果吃食物，尾巴不動，所有身體部分都是危險的
            int limit = snake.size();
            if (!eat_food) {
                limit--; // 忽略尾巴，因為它會移動
            }
            
            for (int k = 0; k < limit; ++k) {
                if (snake[k].first == next_x && snake[k].second == next_y) {
                    collision = true;
                    break;
                }
            }

            if (collision) {
                goto end_game;
            }

            // 移動蛇頭
            head_x = next_x;
            head_y = next_y;
            snake.push_front({head_x, head_y});

            // 檢查是否吃到食物
            if (grid[head_y][head_x] == '$') {
                // 吃到食物，變長，不移除尾巴，並將該格標記為空
                grid[head_y][head_x] = 'o';
            } else {
                // 沒吃到食物，移除尾巴
                snake.pop_back();
            }
        }
    }

end_game:
    // 輸出結果：從頭到尾的座標
    for (const auto& p : snake) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
