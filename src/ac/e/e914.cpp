#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    while (std::cin >> n) {
        std::vector<int> ans;
        for (int d = 1; d <= 99; ++d) {
            int m;
            if (d < 10) {
                m = d * 10;                     // single‑digit case
            } else {
                m = (d % 10) * 10 + d / 10;     // two‑digit reversal
            }
            if (m < 18 || m > 99) continue;    // mother’s present age limits
            if (m + n > 99) continue;          // mother must stay ≤99 after n years
            if (m + n == 2 * (d + n)) {
                ans.push_back(d);
            }
        }
        if (ans.empty()) {
            std::cout << "no answer\n";
        } else {
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i) std::cout << ' ';
                std::cout << ans[i];
            }
            std::cout << '\n';
        }
    }
    return 0;
}
