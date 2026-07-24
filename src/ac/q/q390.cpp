#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, H;
    // 持續讀取至 EOF，以應付多筆測資
    while (cin >> N >> H) {
        // 建立桶子，索引從 1 到 H
        vector<vector<int>> buckets(H + 1);

        string line;
        // 讀取換行符
        getline(cin, line); 

        // 讀取 N-1 行，第 i 行代表第 i 條與第 i+1 條縱線間的橫線
        for (int i = 1; i < N; ++i) {
            getline(cin, line);
            stringstream ss(line);
            int h;
            // 將該縫隙的橫線高度放入對應的桶中，並記錄縫隙編號 i
            while (ss >> h) {
                if (h >= 1 && h <= H) {
                    buckets[h].push_back(i);
                }
            }
        }

        // 初始化終點陣列，pos[i] 代表第 i 條縱線底部的起點編號
        vector<int> pos(N + 1);
        for (int i = 1; i <= N; ++i) {
            pos[i] = i;
        }

        // 從高度 1 到 H 進行模擬
        for (int h = 1; h <= H; ++h) {
            // 同一高度的橫線必不相鄰，交換順序不影響結果
            for (int gap : buckets[h]) {
                swap(pos[gap], pos[gap + 1]);
            }
        }

        // 輸出結果
        for (int i = 1; i <= N; ++i) {
            cout << pos[i];
            if (i < N) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
