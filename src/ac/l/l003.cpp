#include <cstdio>

int main() {
    int board[10][10] = {0};
    int y, x;
    int step = 1;
    while (scanf(" (%d,%d)", &y, &x) == 2) {
        if (y >= 1 && y <= 10 && x >= 1 && x <= 10) {
            board[y-1][x-1] = step;
            step++;
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (board[i][j] == 0) {
                putchar('-');
            } else {
                printf("%d", board[i][j]);
            }
        }
        putchar('\n');
    }
    return 0;
}
