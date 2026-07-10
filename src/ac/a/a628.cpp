#include <cstdio>
#include <cstring>

int main() {
    int n;
    bool first = true;
    while (scanf("%d", &n) == 1) {
        if (!first) printf("\n");
        first = false;

        int grid[19][19];
        memset(grid, 0, sizeof(grid));

        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, -1, 0, 1};

        int x = n / 2, y = n / 2;
        grid[y][x] = 0;
        int dir = 0;
        int val = 1;
        int seglen = 1;
        int total = n * n;

        while (val < total) {
            for (int rep = 0; rep < 2 && val < total; rep++) {
                for (int s = 0; s < seglen && val < total; s++) {
                    x += dx[dir];
                    y += dy[dir];
                    grid[y][x] = val++;
                }
                dir = (dir + 1) % 4;
            }
            seglen++;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%4d", grid[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
