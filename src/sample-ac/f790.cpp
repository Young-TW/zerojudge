#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 數字轉國字
string numToChinese(int n) {
    if (n == 2) return "雙";
    if (n == 3) return "參";
    if (n == 4) return "肆";
    if (n == 5) return "伍";
    if (n == 6) return "陸";
    if (n == 7) return "柒";
    if (n == 8) return "捌";
    if (n == 9) return "玖";
    if (n == 10) return "拾";
    return "";
}

int main() {
    vector<string> board(7);
    while (cin >> board[0]) {
        for (int i = 1; i < 7; ++i) {
            cin >> board[i];
        }

        int countDeadFour = 0;
        int countLiveFour = 0;
        int countLiveThree = 0;

        // 四個方向：橫、直、主斜、副斜
        int dx[] = {0, 1, 1, 1};
        int dy[] = {1, 0, 1, -1};

        // 輔助函數：檢查某個位置是否為 'o'
        auto isO = [&](int r, int c) {
            return r >= 0 && r < 7 && c >= 0 && c < 7 && board[r][c] == 'o';
        };

        // 輔助函數：檢查某個位置是否為 'x' (空地)
        auto isX = [&](int r, int c) {
            return r >= 0 && r < 7 && c >= 0 && c < 7 && board[r][c] == 'x';
        };

        // 遍歷每個格子作為起點，檢查四個方向
        for (int r = 0; r < 7; ++r) {
            for (int c = 0; c < 7; ++c) {
                if (board[r][c] != 'o') continue;

                for (int dir = 0; dir < 4; ++dir) {
                    // 只從序列的起始點開始檢查，避免重複計算
                    int pr = r - dx[dir];
                    int pc = c - dy[dir];
                    if (isO(pr, pc)) continue; // 如果前一個也是 'o'，則不是起點

                    // 收集連續的 'o'
                    vector<pair<int, int>> stones;
                    int cr = r, cc = c;
                    while (isO(cr, cc)) {
                        stones.push_back({cr, cc});
                        cr += dx[dir];
                        cc += dy[dir];
                    }

                    int len = stones.size();
                    if (len == 0) continue;

                    // 檢查兩端
                    bool startOpen = isX(r - dx[dir], c - dy[dir]);
                    bool endOpen = isX(cr, cc);

                    if (len == 3) {
                        // 檢查活三類型 1: 連續三顆 ooo
                        if (startOpen && endOpen) {
                            countLiveThree++;
                        }
                        
                        // 檢查活三類型 2: 中間空一格 oxo, xox, oox? 
                        // 題目定義：同一直線或斜線上的三顆白旗，中間空一格，且兩端皆為空地
                        // 這意味著我們需要檢查形如 o-x-o 的模式，總長度為 5 (包含兩端空地)
                        // 但我們的循環是基於連續的 'o'。對於 o-x-o 這種情況，上面的 while 循環只會抓到單個 'o' 或兩個分開的 'o'。
                        // 所以我们需要单独处理 "跳活三" (o-x-o) 的情况。
                        // 只有當當前是第一個 'o'，且下一個是 'x'，再下一個是 'o'，再下一個是 'o' (不對，是三顆棋子)
                        // 題目範例圖示：
                        // xxxoxxx
                        // xxooxox -> 這裡是 o-o-x-o ? 不，看圖示是 o o x o x ?
                        // 讓我們重新解讀題目關於 "中間空一格" 的描述：
                        // "同一直線或斜線上的三顆白旗，中間空一格"
                        // 這通常指 o-o-x-o (錯) 或是 o-x-o-o (錯) 或是 o-x-o (只有兩顆?)
                        // 再看範例圖：
                        // xxxoxxx
                        // xxooxox  <- 這一行的排列是 o, o, x, o, x ? 不像三顆。
                        // 讓我們看右邊的圖示：
                        // xxxxoxx
                        // xxxxxxx
                        // xxoxxxx
                        // xoxxxxx
                        // 這是一個斜線：o (4,1), x (3,2), o (2,3), o (1,4)? 不對。
                        // 讓我們仔細看第二個活三的圖示：
                        // 左圖：
                        // row 3: xxooxox -> 索引 2,3 是 o, 4 是 x, 5 是 o? 這樣是三顆嗎？2,3,5 -> 不是直線等距。
                        // 啊，我看錯了圖示的對齊。
                        // 讓我們看文字描述："同一直線或斜線上的三顆白旗，中間空一格"
                        // 這一定是 o - x - o - o ? 不，那是四顆。
                        // 一定是 o - x - o (兩顆) ? 不，題目說三顆。
                        // 那就是 o - o - x - o ? (三顆棋子，中間夾一個空) -> 總共佔 4 格？
                        // 或者是 o - x - o - o ?
                        // 或者是 o - x - o (然後另一個在哪？)
                        // 標準五子棋術語中，"跳活三" 指的是 o-x-oo 或 oo-x-o 或 o-x-o (如果是三顆的話，必須是 o-x-o 加上另一顆？)
                        // 不，標準的 "跳三" 是三顆棋子，中間有一個空隙。例如：o o x o (黑黑空白黑) 或者 o x o o。
                        // 讓我們再看一次圖示的座標。
                        // 左邊第二個圖：
                        // row 3: xxooxox -> 假設索引從 0 開始。
                        // x x o o x o x -> o at 2, 3, 5. 這不是直線等距。
                        // 等等，圖示可能是：
                        // row 3: x x o o x o x (2,3 是連的，5 是分開的) -> 這不是直線。
                        // 讓我重新閱讀圖示的排版，可能換行了或是我對齊錯了。
                        // 圖示：
                        // xxxxxxx
                        // xxxxxxx
                        // xxxxxxx
                        // xxooxox
                        // xxxxxxx
                        // xxxxxxx
                        // xxxxxxx
                        // 這看起來像橫向。如果這是 "三顆白棋...中間空一格"，那只能是 o o x o (2,3,5? 不等距) 或是 o x o o (2,4,5? 不等距)。
                        // 除非... 圖示中的 'x' 不一定是空地，而是表示非白棋？但題目說 "空地(x)"。
                        // 讓我們看右邊的斜線圖示：
                        // xxxxoxx (row 2, col 4 is o)
                        // xxxxxxx
                        // xxoxxxx (row 4, col 2 is o) -> 這不對，斜率不對。
                        // 讓我們假設圖示是：
                        // row 2: ...o.. (col 4)
                        // row 3: ......
                        // row 4: ..o... (col 2) -> 這不是直線。
                        
                        // 重新對齊右側圖示：
                        // xxxxoxx
                        // xxxxxxx
                        // xxoxxxx
                        // xoxxxxx
                        // 如果這是斜線，應該是 (2,4), (3,3), (4,2), (5,1)?
                        // 圖示中：
                        // Row 2: xxxxoxx -> o at 4
                        // Row 3: xxxxxxx -> all x
                        // Row 4: xxoxxxx -> o at 2 ?? 如果是斜線應該是 3.
                        // Row 5: xoxxxxx -> o at 1
                        // 這圖示畫得非常奇怪，或者我複製貼上時縮進亂了。
                        
                        // 讓我們回歸文字定義，這通常是最準確的：
                        // "同一直線或斜線上的三顆白旗，中間空一格，且兩端皆為空地"
                        // 在五子棋中，這指的是 "跳活三"。
                        // 形式有兩種：
                        // 1. o o x o (連續兩顆，空一格，一顆) -> 棋子位置 i, i+1, i+3
                        // 2. o x o o (一顆，空一格，連續兩顆) -> 棋子位置 i, i+2, i+3
                        // 注意：o x o x o 是 "跳四" 或 "雙三" 的素材，但這裡只談三顆。
                        // 如果是 o x o (只有兩顆棋子)，那不符合 "三顆白棋"。
                        // 所以一定是三顆棋子，分佈在 4 個格子內，中間有一個空格。
                        // 模式 A: o o x o ( indices: 0, 1, 3 ) -> 空格在 2
                        // 模式 B: o x o o ( indices: 0, 2, 3 ) -> 空格在 1
                        // 條件：兩端必須是空地。
                        // 對於模式 A (o o x o): 範圍是 [start, start+3]。
                        // 棋子在 start, start+1, start+3。空格在 start+2。
                        // 左端：start-1 必須是 x。
                        // 右端：start+4 必須是 x。
                        // 對於模式 B (o x o o): 範圍是 [start, start+3]。
                        // 棋子在 start, start+2, start+3。空格在 start+1。
                        // 左端：start-1 必須是 x。
                        // 右端：start+4 必須是 x。
                        
                        // 我們需要在這裡處理這些情況。
                        // 由於我們的主循環是找連續的 'o'，這些跳躍的情況不會被上面的 `while(isO)` 完整捕捉（只會捕捉到 oo 或 o）。
                        // 所以我們需要在這裡特別檢查。
                        // 為了避免重複計算，我們只在該序列的 "最左/最上" 端點進行檢查。
                        
                        // 檢查模式 A: o o x o
                        // 當前如果是連續兩個 o (len>=2)，且後面隔一個是 o
                        if (len >= 2) {
                            // 檢查 o o x o
                            // 當前起點 r,c 是第一個 o。第二個是 r+d, c+d。
                            // 第三個應該是 r+3d, c+3d。中間 r+2d, c+2d 必須是 x。
                            int r3 = r + 3 * dx[dir];
                            int c3 = c + 3 * dy[dir];
                            int r2 = r + 2 * dx[dir];
                            int c2 = c + 2 * dy[dir];
                            
                            if (isO(r3, c3) && !isO(r2, c2) && isX(r2, c2)) {
                                // 確保這是這個模式的起點 (前面沒有 o)
                                // 前面已經檢查過 isO(pr, pc) 為 false，所以 start-1 不是 o。
                                // 現在檢查兩端空地：
                                // 左端：pr, pc (已確定不是 o，需確認是 x)
                                // 右端：r+4d, c+4d
                                int r4 = r + 4 * dx[dir];
                                int c4 = c + 4 * dy[dir];
                                
                                if (isX(pr, pc) && isX(r4, c4)) {
                                    countLiveThree++;
                                }
                            }
                        }
                        
                        // 檢查模式 B: o x o o
                        // 當前如果是單個 o (len==1)，且後面隔一個是連續兩個 o
                        if (len == 1) {
                            int r2 = r + 2 * dx[dir];
                            int c2 = c + 2 * dy[dir];
                            int r3 = r + 3 * dx[dir];
                            int c3 = c + 3 * dy[dir];
                            int r1 = r + 1 * dx[dir];
                            int c1 = c + 1 * dy[dir];
                            
                            if (isO(r2, c2) && isO(r3, c3) && !isO(r1, c1) && isX(r1, c1)) {
                                // 確保 r2, r3 後面沒有延續成四個？
                                // 題目定義是 "三顆白棋"。如果變成 o x o o o，那就是活四或死四了，不算活三。
                                // 檢查 r+4d 是否是 o? 如果是，則構成四顆，不應計為活三。
                                int r4 = r + 4 * dx[dir];
                                int c4 = c + 4 * dy[dir];
                                if (!isO(r4, c4)) {
                                    // 檢查兩端
                                    // 左端：pr, pc
                                    // 右端：r4, c4 (需為 x)
                                    if (isX(pr, pc) && isX(r4, c4)) {
                                        countLiveThree++;
                                    }
                                }
                            }
                        }
                    } else if (len == 4) {
                        // 活四：兩端皆為空地
                        if (startOpen && endOpen) {
                            countLiveFour++;
                        }
                        // 死四：只有一端為空地
                        else if (startOpen || endOpen) {
                            countDeadFour++;
                        }
                    }
                }
            }
        }

        string result = "";
        if (countDeadFour > 0) {
            if (countDeadFour > 1) result += numToChinese(countDeadFour);
            result += "死四";
        }
        if (countLiveFour > 0) {
            if (countLiveFour > 1) result += numToChinese(countLiveFour);
            result += "活四";
        }
        if (countLiveThree > 0) {
            if (countLiveThree > 1) result += numToChinese(countLiveThree);
            result += "活三";
        }

        cout << result << endl;
    }
    return 0;
}
