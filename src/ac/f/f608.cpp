#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    while (std::cin >> n) {
        std::vector<std::pair<int, int>> pts;
        pts.reserve(n);
        for (int i = 0; i < n; ++i) {
            int x, y;
            std::cin >> x >> y;
            pts.emplace_back(x, y);
        }

        // sort by x asc, then y asc
        std::sort(pts.begin(), pts.end(),
                  [](const std::pair<int,int>& a,
                     const std::pair<int,int>& b) {
                      if (a.first != b.first) return a.first < b.first;
                      return a.second < b.second;
                  });

        // longest non‑decreasing subsequence of y
        std::vector<int> dp;
        dp.reserve(n);
        for (const auto& p : pts) {
            int y = p.second;
            auto it = std::upper_bound(dp.begin(), dp.end(), y);
            if (it == dp.end())
                dp.push_back(y);
            else
                *it = y;
        }

        std::cout << dp.size() << '\n';
    }
    return 0;
}
