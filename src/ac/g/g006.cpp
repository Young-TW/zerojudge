#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    while (std::cin >> s) {
        int cnt[26] = {0};
        for (char ch : s) {
            if ('A' <= ch && ch <= 'Z')
                ++cnt[ch - 'A'];
        }

        std::vector<std::pair<char, int>> v;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] > 0)
                v.emplace_back(static_cast<char>('A' + i), cnt[i]);
        }

        std::sort(v.begin(), v.end(),
                  [](const std::pair<char, int>& a,
                     const std::pair<char, int>& b) {
                      if (a.second != b.second) return a.second > b.second; // higher freq first
                      return a.first < b.first;                               // alphabetical
                  });

        for (const auto& p : v)
            std::cout << p.first;
        std::cout << '\n';
    }
    return 0;
}
