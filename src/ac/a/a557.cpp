#include <cstdio>
#include <cstring>
using namespace std;

typedef __int128 lll;

lll dp[501][51];

void print128(lll v) {
    if (v == 0) { putchar('0'); return; }
    char buf[64];
    int len = 0;
    while (v > 0) {
        buf[len++] = (char)('0' + (int)(v % 10));
        v /= 10;
    }
    for (int i = len - 1; i >= 0; i--) putchar(buf[i]);
}

int main() {
    int m;
    while (scanf("%d", &m) == 1) {
        for (int q = 0; q < m; q++) {
            int y, i, z;
            scanf("%d %d %d", &y, &i, &z);

            memset(dp, 0, sizeof(dp));
            dp[0][0] = 1;

            for (int mm = 1; mm <= z; mm++) {
                for (int n = mm; n <= y; n++) {
                    for (int k = 1; k <= i; k++) {
                        dp[n][k] += dp[n - mm][k - 1];
                    }
                }
            }

            print128(dp[y][i]);
            putchar('\n');
        }
    }
    return 0;
}
