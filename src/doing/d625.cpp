#include <iostream>
#include <vector>

int main() {
    int n, x, y;
    char index;
    std::cin >> n;
    x = n;
    y = n;
    std::vector<std::vector<char>> v;

    while (y > 0) {
        x = n;
        while (x > 0) {
            std::cin >> index;
            v[y][x] = index;
            x--;
        }

        y--;
    }

    return 0;
}

// 踩地雷真好玩