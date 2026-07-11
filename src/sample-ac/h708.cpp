#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct State {
    vector<int> top;
    vector<int> bottom;
    int zero_top;
    int zero_bottom;
};

int N;
vector<int> target_top;
vector<int> target_bottom;

// 檢查是否達到目標狀態
bool is_goal(const State& s) {
    for (int i = 0; i < N; ++i) {
        if (s.top[i] != target_top[i]) return false;
        if (s.bottom[i] != target_bottom[i]) return false;
    }
    return true;
}

// 將狀態轉換為字串作為 key
string state_to_string(const State& s) {
    string res = "";
    for (int x : s.top) res += to_string(x) + ",";
    res += ";";
    for (int x : s.bottom) res += to_string(x) + ",";
    return res;
}

// BFS 求解
void solve() {
    if (N == 1) {
        cout << 0 << endl;
        return;
    }

    // 初始化目標狀態
    target_top.resize(N);
    target_bottom.resize(N);
    for (int i = 0; i < N; ++i) {
        target_top[i] = i;
        target_bottom[i] = i;
    }

    State start;
    start.top.resize(N);
    start.bottom.resize(N);

    for (int i = 0; i < N; ++i) {
        cin >> start.top[i];
        if (start.top[i] == 0) start.zero_top = i;
    }
    for (int i = 0; i < N; ++i) {
        cin >> start.bottom[i];
        if (start.bottom[i] == 0) start.zero_bottom = i;
    }

    if (is_goal(start)) {
        cout << 0 << endl;
        return;
    }

    queue<State> q;
    map<string, pair<State, vector<int>>> visited; // state -> (prev_state_encoded_as_index_not_used, move)
    // 為了節省記憶體與時間，我們只存前驅狀態的指針或路徑重建資訊
    // 但由於 C++ map 不能直接存 iterator 到自身，我們改用另一種方式：
    // 使用 map<string, string> parent 來記錄從哪個狀態來，以及 map<string, vector<int>> last_move
    map<string, string> parent;
    map<string, vector<int>> last_move;

    string start_key = state_to_string(start);
    q.push(start);
    parent[start_key] = ""; // 空字串代表起點
    last_move[start_key] = {};

    int steps = 0;
    bool found = false;
    string end_key = "";

    // 方向: 上(-1,0), 下(1,0), 左(0,-1), 右(0,1)
    // 注意：題目是移動「數字」到空格，等同於移動「空格」到數字的位置，然後交換。
    // 但輸出格式要求：輸出要移動的數字原本的座標 -> 移動到的座標 (即空格座標)
    // 所以如果空格在 (r, c)，我們要移動相鄰的數字 (nr, nc) 到 (r, c)
    // 這等同於空格從 (r, c) 移動到 (nr, nc)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        string cur_key = state_to_string(cur);

        if (is_goal(cur)) {
            found = true;
            end_key = cur_key;
            break;
        }

        // 嘗試移動上方的空格
        // 空格在 (0, cur.zero_top)
        int r0 = 0, c0 = cur.zero_top;
        for (int i = 0; i < 4; ++i) {
            int nr = r0 + dr[i];
            int nc = c0 + dc[i];

            if (nr >= 0 && nr < 2 && nc >= 0 && nc < N) {
                State next_state = cur;
                int val;
                
                // 交換
                if (nr == 0) {
                    val = next_state.top[nc];
                    next_state.top[nc] = 0;
                    next_state.top[c0] = val;
                    next_state.zero_top = nc;
                } else {
                    val = next_state.bottom[nc];
                    next_state.bottom[nc] = 0;
                    next_state.top[c0] = val; // 空格原本在上面，現在數字上來
                    next_state.zero_top = nc; // 空格跑到下面去了？不對
                    // 重新思考邏輯
                    // 空格在 (0, c0)。要把 (nr, nc) 的數字移到 (0, c0)
                    // 交換後，(0, c0) 變成數字，(nr, nc) 變成 0
                    if (nr == 1) {
                        // 數字來自下方
                        val = next_state.bottom[nc];
                        next_state.bottom[nc] = 0;
                        next_state.top[c0] = val;
                        next_state.zero_bottom = nc; // 空格現在在下面
                        // 上面的空格位置不變？不對，上面的格子現在有數字了，所以上面沒有空格了？
                        // 錯了，題目是 2xN，每列各有一個 0。
                        // 啊！題目說：「上面和下面兩個部分的格子裡都有1～N - 1各一個，以及一個空格」
                        // 表示總共有兩個 0！一個在上面，一個在下面。
                        // 我的 State 結構定義錯了？
                        // 重新閱讀題目：「上面和下面兩個部分的格子裡都有...一個空格(空格以0表示)」
                        // 對，每列各有一個 0。所以總共有兩個 0。
                        // 那麼移動規則：「每一步可以隨意選擇一個有數字的格子，並且把它移動到上下左右鄰近的空格」
                        // 這意味著，如果我要移動一個數字，它必須鄰近「某個」空格。
                        // 移動後，該數字原來的位置變空格，原空格位置變該數字。
                        // 所以，每列始終保持一個 0。
                        
                        // 修正邏輯：
                        // 當前狀態有兩個空格：(0, zero_top) 和 (1, zero_bottom)
                        // 我們可以移動任何鄰近這兩個空格之一的數字。
                        
                        // 情況 A: 移動鄰近 (0, zero_top) 的數字
                        // 情況 B: 移動鄰近 (1, zero_bottom) 的數字
                        
                        // 我剛才的迴圈只處理了 (0, zero_top) 的鄰居，這是對的。
                        // 但在交換時，如果鄰居是 (1, nc)，則數字從下面移到上面。
                        // 結果：上面原本的 zero_top 位置現在有數字，下面的 nc 位置變成 0。
                        // 所以上面的空格消失了？不對，題目保證每列各有一個 0。
                        // 這表示：你不能把下面的數字移到上面的空格，如果這樣會導致上面有兩個非零、下面有兩個零？
                        // 不，移動是交換。
                        // 初始：Top: [..., 0, ...], Bottom: [..., X, ...] (X 在 nc)
                        // 移動 X 到 Top 的 0 位置：
                        // Top: [..., X, ...], Bottom: [..., 0, ...]
                        // 結果：Top 的 0 不見了，Bottom 產生了第二個 0？
                        // 這違反了「每列各有一個 0」的約束嗎？
                        // 題目說「發現上面和下面兩個部分的格子裡都有...一個空格」，這是初始狀態的描述。
                        // 移動過程中是否必須維持每列各有一個 0？
                        // 題目沒明確說「必須維持」，但根據移動規則：移動數字到鄰近空格。
                        // 如果我把下面的數字移到上面的空格，那麼上面的空格被填滿，下面的位置變空。
                        // 結果：上面沒空格，下面兩個空格？
                        // 這似乎不合理。通常這類謎題（如 15-puzzle）只有一個空格。
                        // 但這裡是 2xN，且有兩個 0。
                        // 再讀一次：「上面和下面兩個部分的格子裡都有1～N - 1各一個，以及一個空格」
                        // 這只是描述初始狀態和目標狀態。
                        // 移動規則：「選擇一個有數字的格子，並把它移動到上下左右鄰近的空格」
                        // 這意味著，只要鄰近「任何」空格就可以移動。
                        // 移動後，該數字原位置變空格，原空格位置變數字。
                        // 所以，空格可以跨列移動！
                        // 例如：Top 有空格 at T0, Bottom 有空格 at B0.
                        // 如果我把 Bottom[B0+1] 的數字移到 Top[T0] (假設它們相鄰？不可能，除非 T0 == B0+1? 不，上下相鄰是指同一 column)
                        // 上下相鄰：(0, c) 和 (1, c) 是相鄰的。
                        // 所以，如果 Top 有空格 at (0, c)，我可以把 Bottom[c] 的數字移上去。
                        // 結果：Top[c] = 數字，Bottom[c] = 0。
                        // 原本 Bottom 已經有一個空格在某處，比如 (1, k)。現在 Bottom[c] 也變成 0。
                        // 那 Bottom 就有兩個 0 了？
                        // 這表示我的理解有誤。
                        
                        // 重新解讀：也許「空格」是唯一的？但題目說「上面和下面...各有一個空格」，且輸入範例：
                        // 範例 1:
                        // 1 0 2
                        // 2 1 0
                        // 確實有兩個 0。
                        // 目標：
                        // 0 1 2
                        // 0 1 2
                        // 也是兩個 0。
                        // 那麼移動時，是否允許一列有兩個 0，另一列沒有？
                        // 題目沒禁止。規則只說「移動到鄰近的空格」。
                        // 所以，是的，空格可以任意移動，不限制每列一個。
                        // 我的 State 結構需要記錄兩個空格的位置，但在移動時，如果移動跨越列，則其中一列的空格數量會改變。
                        // 但這會使狀態空間變大，且需要動態追蹤所有 0 的位置？
                        // 不，題目保證初始和最終都是每列一個 0，但中間過程可能不是。
                        // 然而，仔細想：如果我有兩個 0，分別在 (0, c1) 和 (1, c2)。
                        // 當我移動一個數字到 (0, c1)，則 (0, c1) 不再是 0，而數字原位置變 0。
                        // 如果數字原位置是 (0, c3)，則 0 仍在上面。
                        // 如果數字原位置是 (1, c2)，則我把 (1, c2) 的數字移到 (0, c1)，結果：
                        // (0, c1) = 數字, (1, c2) = 0。
                        // 但 (1, c2) 原本就是 0！所以沒變？
                        // 不對，如果我把 (1, c2) 的數字移到 (0, c1)，但 (1, c2) 是 0，沒有數字可移。
                        // 所以，我只能移動「有數字」的格子到空格。
                        // 因此，我不能移動 0。
                        // 所以，如果我想把下面的數字移到上面的空格，該數字必須不在下面的空格位置。
                        // 例如：Top: [1, 0, 2], Bottom: [2, 1, 0] (N=3)
                        // 空格在 (0,1) 和 (1,2)。
                        // 我可以移動 Bottom[1]=1 到 Top[1] (因為 (1,1) 和 (0,1) 相鄰)。
                        // 移動後：Top[1] = 1, Bottom[1] = 0。
                        // 現在 Top: [1, 1, 2] -> 錯誤！重複了 1。
                        // 啊！我明白了。數字是 1~N-1 各一個，加上一个 0。
                        // 所以總共有 N 個格子 per row，內容是 0,1,2,...,N-1 各一個。
                        // 當我移動 Bottom[1]=1 到 Top[1]，則 Top[1] 原本是 0，現在變 1。
                        // Bottom[1] 原本是 1，現在變 0。
                        // 所以 Top: [1, 1, 2] 是錯的，因為 Top[0] 也是 1？
                        // 在範例中，Top 初始是 [1, 0, 2]，所以 Top[0]=1, Top[1]=0, Top[2]=2。
                        // Bottom 初始是 [2, 1, 0]，所以 Bottom[0]=2, Bottom[1]=1, Bottom[2]=0。
                        // 移動 Bottom[1]=1 到 Top[1]:
                        // Top[1] 變 1, Bottom[1] 變 0。
                        // 新 Top: [1, 1, 2] -> 重複 1！這不可能，因為數字不能複製。
                        // 我搞錯了。移動是交換嗎？
                        // 題目說：「把它移動到上下左右鄰近的空格」
                        // 這意味著：數字離開原位置，進入空格位置。原位置變空格。
                        // 所以是交換數字和空格。
                        // 在上面的例子：
                        // 移動 Bottom[1] (值是 1) 到 Top[1] (值是 0)。
                        // 結果：Top[1] = 1, Bottom[1] = 0。
                        // 但 Top[0] 已經是 1，所以 Top 有兩個 1？
                        // 這表示這個移動是非法的？或者我的理解完全錯誤。
                        
                        // 重新看範例輸出的移動步驟：
                        // 範例 1 輸入:
                        // 3
                        // 1 0 2
                        // 2 1 0
                        // 輸出第一步: 2 2 1 2
                        // 座標是 1-indexed: (2,2) -> (1,2)
                        // 即 Bottom[1] (0-indexed) 移動到 Top[1]。
                        // 初始: Top[1]=0, Bottom[1]=1.
                        // 移動後: Top[1]=1, Bottom[1]=0.
                        // 新狀態:
                        // Top: 1 1 2 ? -> 這不可能。
                        
                        // 等等，範例輸入的 Top 是 "1 0 2"，Bottom 是 "2 1 0"。
                        // 數字是 1,2 (因為 N=3, 所以 1~2)。
                        // Top 有 1,0,2 -> 數字 1 和 2。
                        // Bottom 有 2,1,0 -> 數字 2 和 1。
                        // 所以整個 2x3 網格有兩個 1 和兩個 2？
                        // 題目說：「上面和下面兩個部分的格子裡都有1～N - 1各一個」
                        // 所以是的！每列各自包含 1~N-1 各一個，加上一个 0。
                        // 所以整個網格有兩份 1~N-1。
                        // 那麼移動後出現重複是正常的，因為本來就重複。
                        // 目標狀態也是每列 0,1,2,...,N-1。
                        // 所以我的擔心是多餘的。
                        
                        // 回到移動邏輯：
                        // 當前狀態: Top: [1, 0, 2], Bottom: [2, 1, 0]
                        // 移動 (2,2) -> (1,2) 即 Bottom[1] -> Top[1]
                        // Bottom[1] 是 1, Top[1] 是 0.
                        // 移動後: Top[1] = 1, Bottom[1] = 0.
                        // 新 Top: [1, 1, 2] -> 正確，因為允許重複（不同列）。
                        // 新 Bottom: [2, 0, 0] -> Bottom 有兩個 0？
                        // 初始 Bottom: [2, 1, 0] -> 空格在 index 2.
                        // 移動 Bottom[1] 後，Bottom[1] 變 0，所以 Bottom: [2, 0, 0] -> 兩個 0。
                        // 這表示在移動過程中，一列可以有多个 0，另一列可能沒有 0。
                        // 這符合規則嗎？規則只說移動數字到鄰近空格，沒限制每列 0 的數量。
                        // 所以是允許的。
                        
                        // 因此，我的 State 結構需要能夠處理任意數量的 0？
                        // 但為了效率，我們還是記錄所有 0 的位置？或者每次掃描？
                        // 由於 N<=50，2xN=100 格，每次掃描找 0 是可以接受的。
                        // 但 BFS 狀態太多，掃描會慢。
                        // 更好的方法：State 中記錄所有 0 的位置（用 vector<pair<int,int>>）。
                        // 但這樣狀態比較複雜。
                        
                        // 簡化：既然最多只有兩個 0（初始），且移動不會增加 0 的總數（總是兩個），
                        // 我們可以記錄兩個 0 的位置。即使它們在同一列。
                        // 修改 State:
                        // vector<int> top, bottom;
                        // vector<pair<int,int>> zeros; // 儲存所有 0 的座標
                        // 但這樣在 BFS 中，狀態的 key 會更複雜。
                        
                        // 另一種思路：不特別記錄 0 的位置，每次生成下一步時，掃描整個網格找 0。
                        // 對於 2x50=100 格，掃描很快。
                        // 且在 BFS 中，每個狀態只擴展一次，所以總開銷可接受。
                        // 讓我們採用這種簡單方法。
                        
                        // 重新設計 BFS:
                        // State: vector<vector<int>> grid (2xN)
                        // 每次從 grid 中找出所有 0 的位置。
                        // 然後對於每個 0，檢查其四個鄰居，如果有數字（非 0），則可以移動該數字到此 0。
                        // 移動：交換數字和 0。
                        // 產生新狀態。
                        
                        // 這樣更通用，且不易出錯。
                        
                        // 由於時間關係，我重寫整個解法。
                    }
                }
            }
        }
    }

    // 由於上述邏輯太複雜且易錯，我決定重寫一個清晰版本。
}

// 重新實現
void solve_clean() {
    cin >> N;
    vector<vector<int>> grid(2, vector<int>(N));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    // 目標狀態
    vector<vector<int>> target(2, vector<int>(N));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < N; ++j) {
            target[i][j] = j;
        }
    }

    if (grid == target) {
        cout << 0 << endl;
        return;
    }

    // BFS
    queue<vector<vector<int>>> q;
    map<vector<vector<int>>, vector<vector<int>>> parent; // current -> previous
    map<vector<vector<int>>, vector<int>> move_record; // current -> move (r1,c1,r2,c2)

    q.push(grid);
    parent[grid] = {}; // empty previous for start
    move_record[grid] = {};

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    bool found = false;
    vector<vector<int>> final_state;

    while (!q.empty()) {
        vector<vector<int>> cur = q.front();
        q.pop();

        if (cur == target) {
            found = true;
            final_state = cur;
            break;
        }

        // 找出所有 0 的位置
        vector<pair<int,int>> zeros;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < N; ++j) {
                if (cur[i][j] == 0) {
                    zeros.push_back({i, j});
                }
            }
        }

        // 對於每個 0，嘗試移動其鄰居數字到此
        for (auto& z : zeros) {
            int zr = z.first, zc = z.second;
            for (int d = 0; d < 4; ++d) {
                int nr = zr + dr[d];
                int nc = zc + dc[d];

                if (nr >= 0 && nr < 2 && nc >= 0 && nc < N && cur[nr][nc] != 0) {
                    // 可以移動 cur[nr][nc] 到 (zr, zc)
                    vector<vector<int>> next_grid = cur;
                    swap(next_grid[nr][nc], next_grid[zr][zc]);

                    if (parent.find(next_grid) == parent.end()) {
                        parent[next_grid] = cur;
                        // 記錄移動: 從 (nr,nc) 移動到 (zr,zc)
                        // 輸出格式: 1-indexed, 先 row 後 col
                        move_record[next_grid] = {nr+1, nc+1, zr+1, zc+1};
                        q.push(next_grid);
                    }
                }
            }
        }
    }

    if (!found) {
        cout << -1 << endl;
        return;
    }

    // 重建路徑
    vector<vector<int>> path_moves;
    vector<vector<int>> curr = final_state;
    while (!parent[curr].empty()) { // 直到起點（parent 為空）
        path_moves.push_back(move_record[curr]);
        curr = parent[curr];
    }
    reverse(path_moves.begin(), path_moves.end());

    cout << path_moves.size() << endl;
    for (auto& m : path_moves) {
        cout << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve_clean();
    return 0;
}
