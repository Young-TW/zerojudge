#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int target_n;
bool found_any;

// 將當前的運算子序列轉換為字串並計算結果以驗證（雖然我們是在建構時確保正確，但為了輸出格式）
// 實際上我們需要在遞迴過程中維護當前的數值狀態
struct Term {
    int base_val; // 基礎數字 (1, 2, 3...)
    vector<int> multipliers; // 後續的 *2, *2...
    
    int get_value() const {
        int res = base_val;
        for (int m : multipliers) {
            res *= m;
        }
        return res;
    }
    
    string to_string_repr() const {
        stringstream ss;
        ss << base_val;
        for (int m : multipliers) {
            ss << " * " << m;
        }
        return ss.str();
    }
};

void dfs(int current_num, int current_sum, int last_term_val, vector<Term>& path) {
    if (current_sum == target_n) {
        found_any = true;
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) cout << " + ";
            cout << path[i].to_string_repr();
        }
        cout << "\n";
        return;
    }
    
    if (current_sum > target_n) return;
    if (current_num > target_n) return; // 基礎數字不會超過 n (因為最小加 1)

    // 嘗試對當前數字 current_num 進行多次 *2 操作
    // 我們可以在這裡枚舉當前這個 base number (current_num) 要被乘幾次 2
    // 注意：題目範例顯示只有 *2 出現，且邏輯推斷通常這類題目的倍增是固定的或是特定的
    // 觀察範例: 
    // 28 = 1+2+3+4+5+6+7 (sum=28) -> OK
    // 28 = 1+2+3*2*2+4 = 1+2+12+4 = 19 != 28? 等等，讓我重算範例。
    // 範例輸出: 1 + 2 + 3 * 2 * 2 + 4 
    // 運算優先順序：加法優先於乘法？？？
    // 題目說："注意!!加法優先於乘法"
    // 這意味著 1 + 2 + 3 * 2 * 2 + 4 其實是 ((1+2+3) * 2 * 2) + 4 ???
    // 如果是這樣：(1+2+3)=6, 6*2=12, 12*2=24, 24+4=28. Bingo!
    
    // 重新理解規則：
    // 一般數學是先乘除後加減。
    // 但這題規定 "加法優先於乘法"。
    // 這表示表達式是從左到右掃描，遇到加法就先算前面的總和，然後如果後面接乘法，就用這個總和去乘？
    // 不，看範例結構： "1 + 2 + 3 * 2 * 2 + 4"
    // 如果加法優先，那應該是 (1+2+3) 然後再 *2 *2 然後 +4。
    // 這暗示了運算的結合性是：一連串的加法形成一個群組，然後這個群組的結果可以被後續的乘法作用，直到遇到下一個加法？
    // 或者更簡單的模型：
    // 整個式子是由 "項" (Terms) 透過 "+" 連接。
    // 但是因為加法優先，所以 "A + B * C" 等於 "(A+B) * C"。
    // 這改變了整個解析樹。
    // 讓我們分析範例：
    // 1. `1 + 2 + 3 + 4 + 5 + 6 + 7` = 28. (純加法，沒問題)
    // 2. `1 + 2 + 3 * 2 * 2 + 4`
    //    步驟：
    //    目前累積 sum = 0
    //    讀入 1 -> sum = 1
    //    讀入 + 2 -> sum = 1+2 = 3
    //    讀入 + 3 -> sum = 3+3 = 6
    //    讀入 * 2 -> sum = 6*2 = 12 (因為加法優先，前面的和先算出來再乘)
    //    讀入 * 2 -> sum = 12*2 = 24
    //    讀入 + 4 -> sum = 24+4 = 28.
    //    結果 28. 符合！
    
    // 3. `1 * 2 + 2 + 3 * 2 * 2`
    //    讀入 1 -> sum = 1
    //    讀入 * 2 -> sum = 1*2 = 2 (這裡沒有前置加法，直接乘？或是初始視為 sum=0, +1, *2?)
    //    如果是 0+1*2 = 2.
    //    讀入 + 2 -> sum = 2+2 = 4
    //    讀入 + 3 -> sum = 4+3 = 7
    //    讀入 * 2 -> sum = 7*2 = 14
    //    讀入 * 2 -> sum = 14*2 = 28
    //    結果 28. 符合！
    
    // 4. `1 * 2 + 2 * 2 * 2 + 3 + 4 + 5`
    //    1 -> 1
    //    *2 -> 2
    //    +2 -> 4
    //    *2 -> 8
    //    *2 -> 16
    //    +3 -> 19
    //    +4 -> 23
    //    +5 -> 28
    //    符合！
    
    // 規則總結：
    // 從左到右處理。
    // 維護一個當前累積值 `current_val`。
    // 第一個數字直接作為 `current_val`。
    // 之後的操作：
    //   如果是 `+ x`: `current_val = current_val + x`
    //   如果是 `* x`: `current_val = current_val * x`
    // 關鍵差異在於：一般的數學裡 `a + b * c` 是 `a + (b*c)`。
    // 這裡是 `(a+b) * c` 嗎？
    // 看範例 2: `1 + 2 + 3 * 2 * 2 + 4`
    // 如果按照單純從左到右 (Left-to-Right) 計算：
    // (((((1 + 2) + 3) * 2) * 2) + 4)
    // = ((3 + 3) * 2 * 2) + 4
    // = (6 * 2 * 2) + 4 = 24 + 4 = 28.
    // 是的！所謂 "加法優先於乘法" 在這題的語境下，配合範例來看，其实就是 **嚴格從左到右計算** (Left-Associative for all operators)，忽略傳統的先乘除後加減。
    // 因為如果是傳統優先級，`3 * 2` 會先算，但在 L-to-R 中，`(1+2+3)` 會先算。
    // 所以這題的本質是：用數字 1, 2, 3, ..., k (連續整數) 以及運算子 `+` 和 `*` (且只能是 `*2`? 範例中只出現 `*2`) 來組成表達式。
    // 等等，範例中所有的乘法都是 `* 2`。題目有說只能乘 2 嗎？
    // 題目名稱 "兔子跳鈴鐺"，通常兔子跳是倍增。
    // 輸入說明沒明確說只能乘 2，但範例全是 `* 2`。
    // 再看題目內容 "111" 可能是亂碼或是隱喻。
    // 假設只能使用 `+ next_number` 或 `* 2`。
    // 並且數字必須是 1, 2, 3, ... 連續出現嗎？
    // 範例 1: 1..7
    // 範例 2: 1, 2, 3, (skip?), 4? 不，是 1, 2, 3, 4。中間插入了 *2 *2。
    // 範例 3: 1, 2, 3, 4? 不，是 `1 * 2 + 2 + 3 * 2 * 2`。這裡數字是 1, 2, 3。結束了？
    // 讓我們檢查範例 3 的數字序列：1, 2, 3。最後一項是 3 嗎？
    // `1 * 2 + 2 + 3 * 2 * 2`
    // 數字出現順序：1, 2, 3。
    // 範例 4: `1 * 2 + 2 * 2 * 2 + 3 + 4 + 5` -> 數字 1, 2, 3, 4, 5。
    // 範例 5: `1 * 2 * 2 * 2 + 2 + 3 + 4 + 5 + 6` -> 數字 1, 2, 3, 4, 5, 6。
    
    // 結論：
    // 1. 數字必須從 1 開始，連續遞增 (1, 2, 3, ..., k)。
    // 2. 在每個數字之後（或是第一個數字之前？不，第一個數字前不能有運算子），可以選擇：
    //    a. 結束 (如果當前值等於 n)
    //    b. 加入 `+ (next_num)`
    //    c. 加入 `* 2` (可以連續多次)
    // 但是要注意順序。表達式是由數字和運算子交錯組成。
    // 結構一定是： Num1 [Op] Num2 [Op] Num3 ...
    // 其中 Op 可以是 `+` 或 `*`。
    // 但根據範例，乘法後面不會直接跟數字？
    // 範例：`3 * 2 * 2 + 4`。這裡 `* 2` 後面是 `* 2`，然後是 `+ 4`。
    // 有沒有 `3 * 2 + 4`？有，隐含在邏輯中。
    // 有沒有 `3 + 4 * 2`？有，範例 4 的尾端 `... + 3 + 4 + 5` (沒乘)，但如果後面還有呢？
    // 重點：數字必須是連續的 1, 2, 3...
    // 運算子放在數字之間。
    // 但是在兩個數字之間，可以有多个 `* 2` 嗎？
    // 範例：`3 * 2 * 2 + 4`。在 3 和 4 之間，插入了 `* 2 * 2`。
    // 所以模式是：
    // Start with val = 1.
    // Current number index = 1.
    // Loop:
    //   Option A: Multiply by 2 (val *= 2). Record "* 2". (Can repeat)
    //   Option B: Add next number (val += next_num). Record "+ next_num". Increment next_num.
    //   Check if val == n. If so, print and return (or continue to find more? 題目要求輸出所有方法，看範例輸出了多行)。
    //   需要搜尋所有可能。
    
    // 參數設計：
    // current_val: 目前計算結果
    // next_num: 下一個要加的數字 (從 2 開始，因為 1 已經用過了)
    // path: 記錄目前的運算子與數字序列，用於輸出
    
    // 初始狀態：
    // current_val = 1
    // next_num = 2
    // path = "1"
    
    // 遞迴步驟：
    // 1. 如果 current_val == n: 輸出 path, found=true. (注意：不能馬上 return，因為可能有更長的序列？
    //    但題目範例似乎是按照某種順序輸出。
    //    觀察範例順序：
    //    1. 全加 (1+..+7)
    //    2. 中間乘 (1+2+3*2*2+4)
    //    3. 前面乘 (1*2+2+3*2*2) -> 這裡數字只到 3? 等等，範例 3 是 `1 * 2 + 2 + 3 * 2 * 2`。
    //       計算：1*2=2, +2=4, +3=7, *2=14, *2=28.
    //       這裡數字用到 3。結束。
    //    4. `1 * 2 + 2 * 2 * 2 + 3 + 4 + 5` -> 數字到 5.
    //    5. `1 * 2 * 2 * 2 + 2 + 3 + 4 + 5 + 6` -> 數字到 6.
    //    
    //    看起來只要 current_val == n 就是一個解，無論是否用完某些數字？
    //    不，數字必須連續。如果在某個點達到了 n，遊戲就結束了嗎？
    //    題目說 "達到分數 n 的方法"。一旦達到 n，就可以停止。
    //    所以只要 current_val == n，就是一個有效解。
    //    但是否允許在達到 n 之後繼續操作？例如 n=5, 1+2+3=6 (超過), 不行。
    //    如果 1*2+3 = 5. 達到。如果繼續 +4 就變 9。
    //    所以當 current_val == n 時，這是一個終止狀態。我們記錄下來。
    //    是否需要繼續搜尋？例如是否有機會 *2 後再減回來？不可能，因為只有 + 和 *2，數字都是正的，值只會增加 (除非 *2 前是 0，但最小是 1)。
    //    既然值單調遞增 (對於 +next_num, next_num>=2; 對於 *2, val>=1)，一旦達到 n，任何進一步的操作都會使值 > n。
    //    例外：如果 current_val 是 0? 不可能，起始 1。
    //    所以一旦 current_val == n，這就是葉節點，不需要再往下搜。
    
    // 剪枝：
    // 如果 current_val > n: return.
    
    // 搜尋策略：
    // 在每一步，我們可以：
    // 1. 如果 current_val == n: 記錄答案。
    // 2. 嘗試 `* 2`: new_val = current_val * 2. 如果 new_val <= n, 遞迴。
    // 3. 嘗試 `+ next_num`: new_val = current_val + next_num. 如果 new_val <= n, 遞迴。
    
    // 順序問題：範例輸出的順序是什麼？
    // 範例 1 (n=5):
    // cheat! (這是什麼？哦，題目內容寫 "111"，範例輸出第一行是 "cheat!" 對應輸入 5?
    // 讓我們看輸入：
    // 5
    // 28
    // 0
    // 輸出：
    // cheat!
    // 1 + 2 + 3 + 4 + 5 + 6 + 7
    // ... (後面都是 28 的解)
    // 啊！輸入 5 的輸出是 "cheat!"。
    // 為什麼？
    // 1+2+3 = 6 > 5.
    // 1*2 = 2. +2 = 4. +3 = 7.
    // 1*2*2 = 4. +2 = 6.
    // 1+2 = 3. *2 = 6.
    // 看來 5 無解？所以輸出 "cheat!"?
    // 題目可能隱含如果無解輸出 "cheat!"。
    // 或者是特定數字 5 有特殊意義？
    // 不管怎樣，如果找不到任何路徑，輸出 "cheat!"。
    
    // 關於輸出順序：
    // 28 的解有 5 個。
    // 順序看起來像是：
    // 1. 盡量多用加法？ (長度最長？)
    // 2. 還是 DFS 的順序？
    // 如果我先試 `+ next_num` 再試 `* 2`：
    // 1 -> +2 (3) -> +3 (6) -> +4 (10) ... -> +7 (28). (找到第一個解：全加)
    // 回溯...
    // 如果在某個點試 `* 2`：
    // 1 -> +2 (3) -> +3 (6) -> *2 (12) -> *2 (24) -> +4 (28). (找到第二個解)
    // 這符合範例順序！
    // 所以 DFS 順序：先嘗試加法，再嘗試乘法。
    
    // 另外，`* 2` 可以連續多次。在 DFS 中，這會自然處理：
    // 狀態 A -> (*2) -> 狀態 B -> (*2) -> 狀態 C.
    
    // 實作細節：
    // path 需要記錄字串。為了效率，可以用 vector<string> 或自定義結構，最後再 join。
    // 由於 N < 400，深度不會太深，字串複製的開銷可接受。
    
    // 修正：題目中的 "cheat!" 是針對 n=5 的情況。
    // 我們需要對每個 n 執行 DFS。如果沒找到任何解，印出 "cheat!"。
    
    // 再次確認 n=5 是否真的無解。
    // Start 1.
    // Path: 1
    // Ops:
    // +2 -> 3.
    //   +3 -> 6 (>5) X
    //   *2 -> 6 (>5) X
    // *2 -> 2.
    //   +2 -> 4.
    //     +3 -> 7 X
    //     *2 -> 8 X
    //   *2 -> 4.
    //     +2 -> 6 X
    //     *2 -> 8 X
    // 確實無解。
    
    // 好的，演算法確定：
    // DFS(current_val, next_num, current_expression_string)
    // Global/Class member: solutions vector<string>
    // Order: Try '+' first, then '*'.
    
    // 但為了避免字串複製過慢，可以用 vector<pair<char, int>> 記錄操作，最後再重建字串。
    // 操作類型：ADD(num), MUL(2).
    // 初始數字 1 固定。
    
    // 最大深度估算：
    // 全加：1+2+...+k ≈ k^2/2 = 400 => k ≈ 28. 深度很小。
    // 全乘：2^k = 400 => k ≈ 9.
    // 混合：深度也很小。
    // 所以直接傳 string 或 vector 都沒問題。
}

// 重新設計 DFS 狀態
// path 儲存操作歷史。
// 初始：val = 1, next_num = 2, path = ["1"]
// 遞迴函數：
void solve_dfs(int current_val, int next_num, vector<string>& path, vector<string>& results) {
    if (current_val == target_n) {
        // Build result string
        stringstream ss;
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) ss << " ";
            ss << path[i];
        }
        results.push_back(ss.str());
        return;
    }
    
    if (current_val > target_n) return;
    // 如果 next_num 已經大於 target_n，再加肯定超過 (因為 current_val >= 1)
    if (next_num > target_n) return;

    // 選擇 1: 加法 (+ next_num)
    // 優先嘗試加法 (根據範例順序推測)
    {
        int next_val = current_val + next_num;
        if (next_val <= target_n) {
            path.push_back("+");
            path.push_back(to_string(next_num));
            solve_dfs(next_val, next_num + 1, path, results);
            path.pop_back();
            path.pop_back();
        }
    }

    // 選擇 2: 乘法 (* 2)
    // 可以連續乘，但在 DFS 框架下，每次呼叫只決定一步。
    // 下一步可以是 *2，然後再遞迴進去決定要不要再 *2 或 +。
    {
        int next_val = current_val * 2;
        if (next_val <= target_n) {
            path.push_back("*");
            path.push_back("2");
            solve_dfs(next_val, next_num, path, results); // next_num 不變
            path.pop_back();
            path.pop_back();
        }
    }
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        target_n = n;
        vector<string> results;
        
        // 初始狀態：數字 1
        // 如果 n==1?
        // 1 = 1. 是否符合？
        // 題目範例沒給 n=1.
        // 如果 n=1, 初始 current_val=1, 直接命中。
        // 輸出 "1"?
        // 但題目說 "兔子跳"，可能需要操作？
        // 不過根據邏輯，1 就是 1。
        // 讓我們假設如果初始就符合，也算一種解。
        
        // 特殊檢查：如果 n=1
        if (n == 1) {
            // 1 是否合法？
            // 輸入範圍 0<=n<400.
            // 如果 n=1, 輸出 "1"?
            // 但看範例格式，都有運算子。
            // 不過 1 本身也是表達式。
            // 先照邏輯跑，如果 DFS 能抓到就抓。
            // 初始 call: current_val=1, next_num=2.
            // 進入函數第一件事檢查 current_val == target.
            // 所以 n=1 會被抓到。
        }

        vector<string> path;
        path.push_back("1");
        
        // 如果 n=1, 上面的 push_back("1") 後，進 DFS 會立即加入 results.
        // 但要注意，如果 n=1，我們不應該繼續做 +2 或 *2，因為會超過。
        // DFS 內部會處理 > n 的剪枝。
        
        // 開始 DFS
        // 注意：如果 n=0? 題目說 n=0 結束，所以不會處理 n=0.
        
        solve_dfs(1, 2, path, results);
        
        if (results.empty()) {
            cout << "cheat!" << endl;
        } else {
            for (const string& s : results) {
                cout << s << endl;
            }
        }
    }
    return 0;
}
