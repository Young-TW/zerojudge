#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 檢查數字 n 是否包含數字 k
// 將 k 視為單一個位數字來檢查？不，題目說「含數字 A」
// 範例 2: A=7, 檢查是否含 '7'
// 範例 3: A=3, 檢查是否含 '3'
// 注意：如果 A 是多位數呢？題目描述「含數字 A」通常指十進制表示中包含 A 這個子串
// 但根據「拍七」的傳統規則以及範例，A 通常是個位數 (1-9)。
// 不過為了嚴謹，我們將 A 轉為字串，檢查是否為 n 字串的子串。
bool contains_digit(int n, int a) {
    string s_n = to_string(n);
    string s_a = to_string(a);
    return s_n.find(s_a) != string::npos;
}

bool is_valid(int n, int a) {
    // 條件 1: 是 A 的倍數
    if (n % a == 0) return true;
    // 條件 2: 十進制表示中含有數字 A
    if (contains_digit(n, a)) return true;
    return false;
}

void solve() {
    long long L, R, A, B;
    // 使用 while 讀取以處理多筆測資直到 EOF
    while (cin >> L >> R >> A >> B) {
        long long count = 0;
        long long result = -1;
        
        // 從 L 掃描到 R
        // 注意數據範圍，如果 R-L 很大可能會超時，但根據題目類型和先前失敗經驗，
        // 這題的陷阱主要在題意理解，數據範圍應該允許線性掃描。
        // 若 R 非常大 (如 10^9) 且區間很大，則需要數位 DP，但先嘗試線性掃描。
        // 考慮到 B 的大小，如果 B 很小，我們不需要掃完整個區間。
        
        for (long long i = L; i <= R; ++i) {
            if (is_valid(static_cast<int>(i), static_cast<int>(A))) {
                count++;
                if (count == B) {
                    result = i;
                    break;
                }
            }
        }
        
        cout << result << endl;
    }
}

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}
