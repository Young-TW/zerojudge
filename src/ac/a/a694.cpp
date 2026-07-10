#include <cstdio>
using namespace std;

int s[505][505];

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int v;
                scanf("%d", &v);
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + v;
            }
        }
        for (int k = 0; k < m; k++) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%d\n", s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]);
        }
    }
    return 0;
}
