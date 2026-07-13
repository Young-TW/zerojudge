#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 定義每個數字 (0-9) 的 7 段顯示狀態
// 順序為: a(上), b(右上), c(右下), d(下), e(左下), f(左上), g(中)
const int segments[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

void print_horizontal_line(int s, bool on) {
    cout << " ";
    if (on) {
        for (int i = 0; i < s; ++i) cout << "-";
    } else {
        for (int i = 0; i < s; ++i) cout << " ";
    }
    cout << " ";
}

void print_vertical_lines(int s, bool left, bool right) {
    if (left) cout << "|";
    else cout << " ";
    
    for (int i = 0; i < s; ++i) cout << " ";
    
    if (right) cout << "|";
    else cout << " ";
}

void solve() {
    int s;
    string n_str;
    
    while (cin >> s >> n_str && (s != 0 || n_str != "0")) {
        int len = n_str.length();
        int height = 2 * s + 3;
        
        // 逐行輸出
        for (int row = 0; row < height; ++row) {
            for (int i = 0; i < len; ++i) {
                int digit = n_str[i] - '0';
                
                if (row == 0) {
                    // 頂部橫線 (段 a)
                    print_horizontal_line(s, segments[digit][0]);
                } else if (row >= 1 && row <= s) {
                    // 上半部垂直線 (段 f, b)
                    print_vertical_lines(s, segments[digit][5], segments[digit][1]);
                } else if (row == s + 1) {
                    // 中間橫線 (段 g)
                    print_horizontal_line(s, segments[digit][6]);
                } else if (row >= s + 2 && row <= 2 * s + 1) {
                    // 下半部垂直線 (段 e, c)
                    print_vertical_lines(s, segments[digit][4], segments[digit][2]);
                } else if (row == 2 * s + 2) {
                    // 底部橫線 (段 d)
                    print_horizontal_line(s, segments[digit][3]);
                }
                
                // 數字之間加一個空格，但最後一個數字後面不加
                if (i < len - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << endl; // 每組測試資料後空一列
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
