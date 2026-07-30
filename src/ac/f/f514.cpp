#include <iostream>
#include <string>
#include <vector>
#include <queue>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string S, T;
    while (std::cin >> S >> T) {
        // positions for every possible character (ASCII)
        std::vector< std::queue<int> > pos(256);
        for (int i = 0; i < static_cast<int>(S.size()); ++i) {
            unsigned char c = static_cast<unsigned char>(S[i]);
            pos[c].push(i + 1);               // 1‑based index
        }

        bool first = true;
        for (char ch_raw : T) {
            unsigned char ch = static_cast<unsigned char>(ch_raw);
            if (!first) std::cout << ' ';
            first = false;

            if (pos[ch].empty()) {
                std::cout << 'X';
            } else {
                std::cout << pos[ch].front();
                pos[ch].pop();
            }
        }
        std::cout << '\n';
    }
    return 0;
}
