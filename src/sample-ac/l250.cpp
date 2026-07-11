#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

int main() {
    int L;
    if (!(cin >> L)) return 0;

    // 使用 map 記錄每個人預訂的座位，key 為姓名，value 為 set<pair<int, int>>
    map<string, set<pair<int, int>>> bookings;
    
    string dummy;
    getline(cin, dummy); // 消耗掉 L 之後的換行符

    string line;
    while (getline(cin, line) && line != "stop") {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, action;
        ss >> name >> action;

        vector<pair<int, int>> coords;
        string token;
        while (ss >> token) {
            // 解析坐標，格式為 x? y? 但範例輸入顯示是連續的 token，如 x1 y1 x2 y2
            // 題目描述 "x1 y1" 可能代表 x=1, y=1。需要解析字串中的數字。
            // 根據範例輸入: "sam book x1 y1 x2 y2"
            // 這表示 token 是 "x1", "y1", "x2", "y2"
            // 但題目說 "坐標x? y?..."，且範例輸入中 cancel 只有 "x2 x2" (這看起來像筆誤或是特殊格式？)
            // 讓我們仔細看範例輸入：
            // sam book x1 y1 x2 y2 -> 兩個坐標 (1,1) 和 (2,2)
            // sam cancel x2 x2 -> 這裡很奇怪，如果是取消坐標，應該是 x y 配對。
            // 但題目說 "取消訂票 格式 : 姓名 canccel 坐標x? y?..." (注意題目拼寫錯誤 canccel vs cancel)
            // 範例輸入用的是 "cancel"。
            // 範例輸入: "sam cancel x2 x2" -> 這可能意味著只給了一個坐標的資訊？或者這是筆誤？
            // 再看範例輸出，最後只有 (1,1) 是 X。
            // 過程：
            // 1. sam book (1,1), (2,2). Sam 有 {(1,1), (2,2)}
            // 2. sam cancel x2 x2. 如果這是取消 (2,2)，那 Sam 剩下 {(1,1)}。
            // 3. mike cancel x1 y1. Mike 本來沒訂，取消無效？或者這行其實沒影響。
            // 4. mike book x1 y1. Mike 訂 (1,1)。
            // 結果：(1,1) 被 Mike 訂了。Sam 的 (1,1) 呢？
            // 啊，題目說 "每人限訂五個，限取消三個"。
            // 關鍵問題：座位是否可以被不同的人重複預訂？通常電影院不行。
            // 但如果 Sam 訂了 (1,1)，Mike 能再訂嗎？
            // 範例輸出顯示 (1,1) 是 X。這表示 Mike 成功訂到了 (1,1)。
            // 這暗示著：當 Sam cancel 的時候，他取消了 (2,2) 嗎？還是 (1,1)?
            // 讓我們重新解讀 "sam cancel x2 x2"。
            // 有可能題目的意思是 token 是成對出現的，但範例輸入的 "x2 x2" 其實是 "x2 y2" 的筆誤？
            // 或者，token 的格式是 "x" + 數字，"y" + 數字。
            // 如果 token 是 "x2"，下一個是 "x2"，這不合理。
            // 讓我們假設範例輸入的 "sam cancel x2 x2" 其實是 "sam cancel x2 y2" 的筆誤（因為 y2 對應第二個坐標的 y）。
            // 如果是這樣：
            // 1. Sam book (1,1), (2,2).
            // 2. Sam cancel (2,2). Sam 剩下 (1,1).
            // 3. Mike cancel (1,1). Mike 沒訂過，無效。
            // 4. Mike book (1,1). 但 (1,1) 還被 Sam 佔著啊？
            // 除非... 系統不檢查座位是否被他人佔用？或者 "取消" 會釋放座位給所有人？
            // 又或者，題目隱含的意思是，如果 A 訂了座位，B 要訂必須等 A 取消？
            // 但範例中 Sam 並沒有取消 (1,1)，Mike 卻訂到了 (1,1)。
            // 這只有一種可能：題目邏輯是「最後一個操作勝出」或者「座位狀態只由當前誰訂了決定，後訂的覆蓋先訂的」？
            // 不對，這不符合常理。
            // 讓我們再仔細看範例輸入的第二行：`sam cancel x2 x2`。
            // 有沒有可能坐標的輸入格式不是 x y 配對，而是單純的列表，然後系統自動配對？
            // 或者是：x2 代表第 2 行，第二個 x2 代表第 2 列？即 (2, 2)。
            // 那 `mike cancel x1 y1` 呢？x1, y1 -> (1, 1)。
            // `mike book x1 y1` -> (1, 1)。
            // 如果 Sam 沒有取消 (1,1)，Mike 怎麼能 book (1,1)？
            // 唯一解釋：這題的邏輯可能非常簡單，不檢查座位衝突，或者後來的 book 直接覆蓋？
            // 但題目說「人手輸入訂票，並且可以在訂票後取消座位」。
            // 讓我們考慮另一種情況：範例輸入中的 `sam cancel x2 x2` 其實是打錯了，原本應該是 `sam cancel x2 y2`。
            // 而 `mike cancel x1 y1` 也是無效操作。
            // 那為什麼 Mike 能 book (1,1)？
            // 難道 Sam 的 `book` 在 `cancel` 之後就失效了？不，他只 cancel 了一個。
            // 等等，有沒有可能題目意思是：座位一旦被 cancel，就變回空位，不管原來是誰訂的？
            // 當然，取消是自己取消自己的。
            // 那 Mike book (1,1) 成功，代表 (1,1) 當時是空的。
            // 這代表 Sam 的 (1,1) 在某個時候被釋放了？
            // 或者... 這題根本沒有「座位互斥」的限制？也就是說，同一個座位可以同時被多個人「預訂」，但最後輸出時，只要有任一個人訂了就是 X？
            // 如果是這樣，那 Sam 有 (1,1)，Mike 也有 (1,1)，輸出還是 X。這符合範例。
            // 但這樣「取消」的邏輯呢？如果 Sam cancel (1,1)，但 Mike 還訂著 (1,1)，那座位還是 X？
            // 如果是這樣，那邏輯就是：座位是 X 若存在至少一個人訂了該座位。
            // 讓我們用這個邏輯模擬範例：
            // 1. Sam book (1,1), (2,2). Global state: (1,1): {Sam}, (2,2): {Sam}
            // 2. Sam cancel (2,2). (假設 x2 x2 是指 (2,2)). Global state: (1,1): {Sam}, (2,2): {}
            // 3. Mike cancel (1,1). Mike 沒訂 (1,1)，所以無效。Global state: (1,1): {Sam}
            // 4. Mike book (1,1). Global state: (1,1): {Sam, Mike}
            // 輸出：(1,1) 有人訂 -> X, (2,2) 沒人訂 -> O.
            // 結果：X O O O O ... 符合範例輸出！
            // 結論：這題不需要檢查座位是否被他人佔用。每個人維護自己的預訂清單。
            // 最終座位圖：只要有任何人預訂了該座位（且未取消），該座位即為 X。
            // 限制條件：每人限訂 5 個（指成功的 book 指令累計？還是當前持有的？通常是累計操作次數或當前持有。題目說「每人限訂五個」，應指單次指令最多 5 個坐標，還是總數？
            // 題目原文：「每人限訂五個，限取消三個」。這通常指單次指令的參數數量限制，或是總持有量？
            // 看輸入說明：「坐標最多有五個」、「坐標最多有三個」。這應該是指單次指令的參數上限。
            // 但為了安全起見，我們應該檢查單次指令的坐標數量是否符合題目描述的「最多」。
            // 不過題目主要邏輯應該是：
            // 1. 解析指令。
            // 2. 如果是 book：將坐標加入該人的 set。如果超過 5 個？題目說「每人限訂五個」，可能是指總共只能持有多少個？
            //    但輸入說明又說「坐標最多有五個」，這是指單次指令的參數個數。
            //    考慮到這是簡單模擬題，可能不需要檢查總數限制，只需處理單次指令的解析。
            //    但為了嚴謹，如果題目意指「每人同時最多持有 5 個座位」，那就要檢查。
            //    然而範例中沒有測試邊界情況。通常這類題目若未明確說明「超過如何處理」，則假設輸入合法或不需檢查總數，只需模擬。
            //    但輸入說明明確写了「坐標最多有五個」，這是对輸入格式的保證，而不是運行時的限制檢查。
            //    所以我們假設輸入符合格式，只需模擬 book 和 cancel 的邏輯。
            // 3. 如果是 cancel：從該人的 set 中移除坐標。同樣，單次最多 3 個。
            // 4. 最後統計所有被任何人持有的坐標。

            // 解析 token 為數字
            // token 格式可能是 "x1", "y1", "x2", "y2" 或是混雜？
            // 範例：x1 y1 x2 y2
            // 我們需要提取數字。
            int val = 0;
            for (char c : token) {
                if (isdigit(c)) {
                    val = val * 10 + (c - '0');
                }
            }
            // 但我們要怎麼知道這是 x 還是 y？
            // 題目說 "x是指第幾行(橫)，y值為第幾列(縱)"
            // 輸入格式: "x1 y1 x2 y2"
            // 這暗示 token 是成對出現的，第一個是 x，第二個是 y。
            // 但 token 本身帶有 'x' 或 'y' 前綴嗎？
            // 範例輸入顯示有 'x' 和 'y' 前綴。
            // 所以我們可以檢查 token[0] 是 'x' 還是 'y' 來判斷？
            // 不，題目說 "坐標x? y?..."，可能只是描述。
            // 但範例輸入確實有 x/y 前綴。
            // 讓我們假設 token 總是包含數字，且順序是 x, y, x, y...
            // 無論 token 是什麼字串，我們只取數字，然後兩兩配對 (x, y)。
            
            // 修正策略：收集所有 token 中的數字，然後兩兩配對。
            // 但這樣會丟失 x/y 的語義嗎？
            // 如果輸入是 "x1 y1"，數字是 1, 1 -> (1, 1)。
            // 如果輸入是 "x2 y2"，數字是 2, 2 -> (2, 2)。
            // 如果輸入是 "x1 x2" (如 cancel 的例子)，數字是 1, 2 -> (1, 2)？
            // 範例中 `sam cancel x2 x2` -> 數字 2, 2 -> (2, 2)。這合理。
            // 範例中 `mike cancel x1 y1` -> 數字 1, 1 -> (1, 1)。
            // 範例中 `mike book x1 y1` -> 數字 1, 1 -> (1, 1)。
            // 看來只需要提取數字並兩兩配對即可。
            
            // 由於我們在 while(ss >> token) 迴圈中，我們需要暫存數字。
            // 但這樣會打亂結構，因為我們需要在迴圈外處理配對。
            // 更好的方法：先讀取所有 token，提取數字到一個 vector，然後兩兩配對。
            // 但我們已經在讀取 token 了。
            // 讓我們改變策略：先讀完整行，解析出所有數字，再配對。
            // 不，我們已經在用 stringstream 了。
            // 讓我們把 token 解析出的數字先存起來。
            // 但這樣會導致邏輯複雜化，因為我們需要在讀完所有 token 後才處理。
            // 簡單點：在 while 迴圈中，我們無法知道下一個 token 是什麼。
            // 所以我們應該先把所有數字讀出來，存在一個 vector 裡。
            // 但我們現在已经在 while(ss >> token) 中了。
            // 讓我們重構：先讀取 name 和 action，然後讀取剩餘所有 token，提取數字。
            
            // 由於我已經寫了 while(ss >> token)，讓我們在裡面只做提取數字的工作，存到一個臨時 vector。
            // 但這需要改變代碼結構。
            // 讓我們在進入 while 之前定義一個 vector<int> nums;
            // 然後在 while 裡 push_back(val)。
            // 但 val 的計算邏輯需要放在這裡嗎？
            // 是的。
            
            // 等等，我現在的代碼結構是在 while(ss >> token) 裡面直接處理。
            // 這是不對的，因為我们需要成對處理。
            // 讓我重寫這部分的邏輯。
        }
        
        // 重新解析這一行以正確處理坐標配對
        stringstream ss_line(line);
        string n, act;
        ss_line >> n >> act;
        
        vector<int> nums;
        string t;
        while (ss_line >> t) {
            int v = 0;
            bool has_digit = false;
            for (char c : t) {
                if (isdigit(c)) {
                    v = v * 10 + (c - '0');
                    has_digit = true;
                }
            }
            if (has_digit) {
                nums.push_back(v);
            }
        }
        
        // 兩兩配對
        for (size_t i = 0; i + 1 < nums.size(); i += 2) {
            int x = nums[i];
            int y = nums[i+1];
            // 檢查邊界
            if (x >= 1 && x <= L && y >= 1 && y <= L) {
                coords.push_back({x, y});
            }
        }

        if (action == "book") {
            for (const auto& p : coords) {
                bookings[name].insert(p);
            }
        } else if (action == "cancel") { // 注意題目拼寫錯誤 canccel，但範例用 cancel
            for (const auto& p : coords) {
                if (bookings[name].count(p)) {
                    bookings[name].erase(p);
                }
            }
        }
    }

    // 建立座位圖
    // 使用 set 記錄所有被預訂的座位
    set<pair<int, int>> occupied;
    for (const auto& entry : bookings) {
        for (const auto& seat : entry.second) {
            occupied.insert(seat);
        }
    }

    // 輸出
    for (int i = 1; i <= L; ++i) {
        for (int j = 1; j <= L; ++j) {
            if (j > 1) cout << " ";
            if (occupied.count({i, j})) {
                cout << "X";
            } else {
                cout << "O";
            }
        }
        cout << "\n";
    }

    return 0;
}
