#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 502;
char grid[MAXN][MAXN];
int qx[MAXN * MAXN], qy[MAXN * MAXN];

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n) == 2) {
        for (int i = 0; i < m; i++) {
            scanf("%s", grid[i]);
        }
        int count = 0;
        int maxSize = 0;
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'J') {
                    count++;
                    int size = 0;
                    int head = 0, tail = 0;
                    qx[tail] = i; qy[tail] = j; tail++;
                    grid[i][j] = 'X';
                    while (head < tail) {
                        int x = qx[head], y = qy[head]; head++;
                        size++;
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 'J') {
                                grid[nx][ny] = 'X';
                                qx[tail] = nx; qy[tail] = ny; tail++;
                            }
                        }
                    }
                    if (size > maxSize) maxSize = size;
                }
            }
        }
        printf("%d %d\n", count, maxSize);
    }
    return 0;
}
