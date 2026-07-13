#include <iostream>
#include <vector>

int main() {
    int n;
    while (std::cin >> n) {
        if (n < 3) {
            // 少於 3 個點無法形成山頭（首尾不計，中間至少需 1 點）
            // 讀掉剩餘輸入
            for (int i = 0; i < n; ++i) {
                int temp;
                std::cin >> temp;
            }
            std::cout << 0 << "\n";
            continue;
        }

        std::vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> h[i];
        }

        int peaks = 0;
        int i = 1;
        while (i < n - 1) {
            // 尋找上升段的終點（高原的開始或單一峰值點）
            if (h[i] > h[i - 1]) {
                int j = i;
                // 越過所有相等的高度（高原）
                while (j < n - 1 && h[j] == h[j + 1]) {
                    j++;
                }
                // 檢查高原/峰值之後是否下降
                if (j < n - 1 && h[j] > h[j + 1]) {
                    peaks++;
                }
                // 從 j 之後繼續掃描，因為 j 已經是下降點的左側或末端
                i = j + 1;
            } else {
                i++;
            }
        }

        std::cout << peaks << "\n";
    }
    return 0;
}
