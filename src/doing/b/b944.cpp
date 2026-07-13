#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> user(n, 0);
    vector<int> time_left(n, 0);
    int a, b;

    bool first_output = true;

    while (cin >> a >> b) {
        // 減少剩餘時間，模擬時間流逝到下一個人到達的瞬間
        // 根據題目邏輯，新來的人會在上一個人使用了一段時間後到達
        // 這裡的邏輯是：每次輸入代表一個事件，事件發生時，所有正在使用的小便斗時間減 1
        // 但範例顯示，第二個人進來時，第一個人的時間從 5 變成 4，代表經過了 1 單位時間
        // 第三個人進來時，時間從 4->3, 4->3 (第二個人剛佔用變 4，然後立刻減 1? 不對)
        
        // 重新分析範例邏輯：
        // 初始: 0 0 0
        // 人 1 (time 5): 找到位置 0。狀態: User[1,0,0], Time[5,0,0]。輸出。
        // 人 2 (time 4): 
        //   先讓現有時間 -1? -> Time[4,0,0]。
        //   尋找位置：
        //     Pos 0: 有人。
        //     Pos 1: 無人。左邊(0)有人，右邊(2)無人。符合"相隔一個"嗎？
        //       題目說："盡量相隔一個小便斗"。意思是優先找兩邊都沒人的。
        //       如果找不到兩邊都沒人的，才找旁邊有人的？
        //       不，題目說："除非他們找不到能夠相鄰一個小便斗的小便斗" -> 這句話語法有點怪。
        //       原文："男生們上廁所都會盡量相隔一個小便斗，除非他們找不到能夠相鄰一個小便斗的小便斗，才會勉為其難的使用其他的小便斗"
        //       這句中文可能有誤，通常是 "除非找不到'兩邊都沒人'的，才找'旁邊有人'的"。
        //       或者是 "盡量相隔" = 優先找左右都空的。
        //       讓我們看範例：
        //       Step 2: Time 先減 1 -> [4, 0, 0]。
        //       人 2 進來。
        //       Pos 0: 使用中。
        //       Pos 1: 空。左邊(0)有人。右邊(2)空。這不是"相隔一個"(兩邊都空)。
        //       Pos 2: 空。左邊(1)空。右邊無。這是"相隔一個"嗎？
        //       範例結果人 2 選了 Pos 2 (編號 2)。
        //       為什麼不選 Pos 1? 因為 Pos 1 旁邊有人 (Pos 0)。Pos 2 旁邊沒人 (Pos 1 是空的)。
        //       所以策略是：優先找 "左右鄰居都沒人" 的位置。
        //       如果找不到，再找 "左右鄰居有人" 的位置 (勉強使用)。
        //       如果還是找不到 (全滿)，則 Not enough。
        //       
        //       回到 Step 2:
        //       當前狀態 (減 1 後): [4, 0, 0] (User: [1, 0, 0])
        //       檢查 Pos 0: 使用中。
        //       檢查 Pos 1: 空。Left=1(有人), Right=0(空)。不符合"兩邊都空"。
        //       檢查 Pos 2: 空。Left=0(空), Right=無(算空)。符合"兩邊都空"。
        //       所以選 Pos 2。設定 User[2]=2, Time[2]=4。
        //       輸出: Number: 1 0 2, Time: 4 0 4。符合範例。
        //
        // Step 3: 人 3 (time 3)
        //   先減 1: Time [3, 0, 3]。
        //   檢查 Pos 0: 使用中。
        //   檢查 Pos 1: 空。Left=1(有人), Right=2(有人)。兩邊都有人。不符合"兩邊都空"。
        //   檢查 Pos 2: 使用中。
        //   第一輪 (找兩邊都空) 失敗。
        //   第二輪 (找勉強可用的):
        //     Pos 1: 空。雖然兩邊有人，但沒得選了。選它。
        //   設定 User[1]=3, Time[1]=3。
        //   輸出: Number: 1 3 2, Time: 3 3 3。符合範例。
        //
        // Step 4: 人 4 (time 2)
        //   先減 1: Time [2, 2, 2]。
        //   檢查所有位置：0(忙), 1(忙), 2(忙)。
        //   找不到空位。
        //   輸出 "  Not enough"。
        //   然後輸出當前狀態 (已經減過 1 的): Number: 1 3 2, Time: 2 2 2。符合範例。
        //
        // Step 5: 人 5 (time 1)
        //   先減 1: Time [1, 1, 1]。
        //   全滿。
        //   輸出 "  Not enough"。
        //   輸出狀態: Number: 1 3 2, Time: 1 1 1。符合範例。

        // 邏輯確認：
        // 1. 每次讀入新人前，先將所有 time_left > 0 的減 1。
        // 2. 嘗試找空位：
        //    Phase 1: 找一個空位 i，使得 (i-1 空或不存在) 且 (i+1 空或不存在)。
        //    Phase 2: 如果 Phase 1 失敗，找任意空位 i。
        //    Phase 3: 如果 Phase 2 失敗，輸出 Not enough。
        // 3. 如果找到，佔用並設定時間。
        // 4. 輸出格式注意：
        //    如果有 Not enough，先印 "  Not enough"，然後換行印狀態。
        //    如果沒有 Not enough，直接印狀態。
        //    但是範例中，成功的案例前面沒有空行，失敗的案例前面有 "  Not enough"。
        //    仔細看範例輸出的空行：
        //    每個案例之間似乎有空行？
        //    範例輸出：
        //    Number...
        //    Time...
        //    (空行)
        //    Number...
        //    Time...
        //    (空行)
        //    ...
        //    Not enough
        //    Number...
        //    Time...
        //    
        //    實際上，題目描述說 "每次輸出共有兩行或三行"。
        //    這意味著每個輸入對應一個區塊。
        //    範例中區塊之間有空行。這可能是因為每個區塊結束後多印了一個 newline?
        //    或是 "Not enough" 那一行前面有空格，而正常情況沒有？
        //    讓我們嚴格比對範例輸出的字元。
        //    範例輸出第一段：
        //    "Number: 1 0 0\n  Time: 5 0 0\n\n" (假設最後有個空行分隔)
        //    第二段：
        //    "Number: 1 0 2\n  Time: 4 0 4\n\n"
        //    第三段：
        //    "Number: 1 3 2\n  Time: 3 3 3\n\n"
        //    第四段：
        //    "  Not enough\nNumber: 1 3 2\n  Time: 2 2 2\n\n"
        //    
        //    觀察提供的 Diff：
        //    期望: ... 3 3 3\n\n  Not enough ...
        //    實際: ... 3 3 3\n  Not enough ...
        //    差別在於 "Not enough" 之前是否有一個空行。
        //    既然題目說 "每次輸出共有兩行或三行"，這暗示每個 Case 的輸出是獨立的。
        //    如果每個 Case 輸出完都加一個 blank line，那麼：
        //    Case 1: 2 lines + blank
        //    Case 2: 2 lines + blank
        //    Case 3: 2 lines + blank
        //    Case 4: 3 lines (Not enough + 2 lines) + blank?
        //    
        //    讓我們看 Diff 的上下文：
        //    期望: ... Time: 3 3 3\n\n  Not enough ...
        //    這表示在第三組輸出的 "Time..." 之後，有兩個換行符，然後才是 "  Not enough"。
        //    也就是說，每個測試案例處理完後，都要多印一個換行符。
        //    
        //    修正策略：在每個案例輸出完畢後（無論是成功還是失敗），都額外輸出一個空行。
        //    但要注意 EOF 時是否需要？通常 Online Judge 忽略末尾空白，但中間的分隔必須正確。
        //    根據 Diff，第三組和第四組之間缺了一個空行。
        //    所以邏輯應該是：
        //    For each input:
        //      Update time
        //      Find spot
        //      If not found: print "  Not enough"
        //      Print status lines
        //      Print an extra newline (to separate from next case)
        //
        //    等等，如果最後一個 case 也印了空行，通常沒問題。
        //    讓我們再確認一次 Diff。
        //    期望: ... 3 3 3\n\n  Not enough ...
        //    實際: ... 3 3 3\n  Not enough ...
        //    這明確指出需要在每個 case 結束後多加一個 \n。

        // Step 1: 時間流逝
        for (int i = 0; i < n; ++i) {
            if (time_left[i] > 0) {
                time_left[i]--;
            }
        }

        int chosen = -1;

        // Step 2: Phase 1 - 找兩邊都沒人的
        for (int i = 0; i < n; ++i) {
            if (user[i] == 0) {
                bool left_empty = (i == 0) || (user[i - 1] == 0);
                bool right_empty = (i == n - 1) || (user[i + 1] == 0);
                
                if (left_empty && right_empty) {
                    chosen = i;
                    break;
                }
            }
        }

        // Step 3: Phase 2 - 找任意空位
        if (chosen == -1) {
            for (int i = 0; i < n; ++i) {
                if (user[i] == 0) {
                    chosen = i;
                    break;
                }
            }
        }

        // Step 4: 處理結果與輸出
        if (chosen == -1) {
            cout << "  Not enough" << endl;
        } else {
            user[chosen] = a;
            time_left[chosen] = b;
        }

        // 輸出狀態
        cout << "Number:";
        for (int i = 0; i < n; ++i) {
            cout << " " << user[i];
        }
        cout << endl;

        cout << "  Time:";
        for (int i = 0; i < n; ++i) {
            cout << " " << time_left[i];
        }
        cout << endl;
        
        // 關鍵修正：每個案例結束後多印一個空行
        cout << endl;
    }

    return 0;
}
