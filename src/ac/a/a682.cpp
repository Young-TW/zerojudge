#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

// 全局變數用於回溯
int n_global;
vector<pair<int, int>> cells; // 儲存 (d1, d2) 斜線索引
bool used_d1[20]; // d1 = r+c, 最大 14 (7+7)
bool used_d2[20]; // d2 = r-c+n-1, 最大 14
long long count_ways[50]; // 記錄放置 i 個主教的方法數

void backtrack(int idx, int placed) {
    if (idx == (int)cells.size()) {
        count_ways[placed]++;
        return;
    }
    
    // 選項 1: 不在當前格子放主教
    backtrack(idx + 1, placed);
    
    // 選項 2: 在當前格子放主教（如果可行）
    int d1 = cells[idx].first;
    int d2 = cells[idx].second;
    
    if (!used_d1[d1] && !used_d2[d2]) {
        used_d1[d1] = true;
        used_d2[d2] = true;
        backtrack(idx + 1, placed + 1);
        used_d1[d1] = false;
        used_d2[d2] = false;
    }
}

// 計算在給定顏色格子中放置主教的方法數
// color: 0 表示 (r+c)%2==0 (白色), 1 表示 (r+c)%2==1 (黑色)
vector<long long> solve_color(int n, int color) {
    cells.clear();
    memset(used_d1, 0, sizeof(used_d1));
    memset(used_d2, 0, sizeof(used_d2));
    
    // 收集該顏色的所有格子，並轉換為斜線座標
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if ((r + c) % 2 == color) {
                int d1 = r + c;          // 範圍: 0 ~ 2n-2
                int d2 = r - c + n - 1;  // 範圍: 0 ~ 2n-2
                cells.push_back({d1, d2});
            }
        }
    }
    
    // 初始化計數器
    int max_pieces = cells.size();
    for (int i = 0; i <= max_pieces; i++) {
        count_ways[i] = 0;
    }
    
    // 執行回溯
    backtrack(0, 0);
    
    // 返回結果
    vector<long long> result(max_pieces + 1);
    for (int i = 0; i <= max_pieces; i++) {
        result[i] = count_ways[i];
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    while (cin >> n >> k && (n != 0 || k != 0)) {
        if (k == 0) {
            cout << 1 << "\n";
            continue;
        }
        
        // 分別計算白色和黑色格子的放置方法數
        vector<long long> white = solve_color(n, 0); // (r+c)%2==0
        vector<long long> black = solve_color(n, 1); // (r+c)%2==1
        
        // 卷積合併：總共放 k 個 = 白色放 i 個 * 黑色放 k-i 個
        long long ans = 0;
        for (int i = 0; i <= k; i++) {
            int j = k - i;
            if (i < (int)white.size() && j < (int)black.size()) {
                ans += white[i] * black[j];
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
