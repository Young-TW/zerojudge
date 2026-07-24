#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string answer;
    if (!(cin >> answer)) return 0;          // answer, length always 5
    int p;
    cin >> p;                                 // number of players
    
    for (int player = 0; player < p; ++player) {
        bool solved = false;                  // 已經猜中
        int guessCnt = 0;                     // 合法猜測次數
        string guess;
        while (cin >> guess) {
            if (guess == "#") break;          // 本玩家結束
            
            if (solved) continue;             // 已猜中，忽略後續輸入
            
            if (guess.size() < 5) {
                cout << "Not enough letters\n";
                continue;                     // 不計入次數
            }
            if (guess.size() > 5) {
                cout << "Too long\n";
                continue;                     // 不計入次數
            }
            
            ++guessCnt;                       // 合法猜測次數 +1
            
            // ----- 第一步：標記全部 O -----
            string result(5, ' ');
            bool usedAns[5] = {false};
            bool usedG[5]   = {false};
            for (int i = 0; i < 5; ++i) {
                if (guess[i] == answer[i]) {
                    result[i] = 'O';
                    usedAns[i] = usedG[i] = true;
                }
            }
            // 計算答案中剩餘字母的頻率
            int freq[26] = {0};
            for (int i = 0; i < 5; ++i) {
                if (!usedAns[i]) ++freq[answer[i] - 'A'];
            }
            // ----- 第二步：從左到右標記 Y 或 X -----
            for (int i = 0; i < 5; ++i) {
                if (usedG[i]) continue;
                int idx = guess[i] - 'A';
                if (freq[idx] > 0) {
                    result[i] = 'Y';
                    --freq[idx];
                } else {
                    result[i] = 'X';
                }
            }
            
            cout << result << "\n";
            
            // 判斷是否全部為 O
            bool allO = true;
            for (char c : result) if (c != 'O') { allO = false; break; }
            if (allO) {
                cout << "Congradulat1ons ! You guessed " << guessCnt << " times\n";
                solved = true;                 // 後續輸入全部忽略
            }
        }
        cout << "\n";                          // 玩家區塊結束，空一行
    }
    return 0;
}
