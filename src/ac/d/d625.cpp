#include <iostream>
#include <string>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> board(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> board[i];
    }

    for (int i = 0; i < n; ++i) {
        std::string line;
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == '*') {
                line += '*';
                continue;
            }
            int count = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue;
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;
                    if (board[ni][nj] == '*') ++count;
                }
            }
            line += (count == 0) ? '-' : static_cast<char>('0' + count);
        }
        std::cout << line << '\n';
    }

    return 0;
}

// 踩地雷真好玩
