#include <iostream>
#include <cstring>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n1;
    while (std::cin >> n1) {
        const int SZ = 20;                 // use indices 1..19
        int board1[SZ][SZ];
        int board2[SZ][SZ];
        // initialise to -1 (empty)
        for (int i = 1; i < SZ; ++i)
            for (int j = 1; j < SZ; ++j)
                board1[i][j] = board2[i][j] = -1;

        for (int i = 0; i < n1; ++i) {
            int x, y, c;
            std::cin >> x >> y >> c;
            board1[x][y] = c;
        }

        int n2;
        std::cin >> n2;
        for (int i = 0; i < n2; ++i) {
            int x, y, c;
            std::cin >> x >> y >> c;
            board2[x][y] = c;
        }

        int diff = 0;
        for (int x = 1; x <= 19; ++x) {
            for (int y = 1; y <= 19; ++y) {
                int a = board1[x][y];
                int b = board2[x][y];
                if (a == -1 && b == -1) continue;
                if (a == -1 || b == -1) diff += 1;
                else if (a != b) diff += 2;
            }
        }

        std::cout << diff << '\n';
    }
    return 0;
}
