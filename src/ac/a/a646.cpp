#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <numeric>

int dp[1005];

int main() {
    int c;
    double p;
    while (scanf("%d %lf", &c, &p) == 2) {
        int p_num = (int)(p * 1000.0 + 0.5);
        if (p_num <= 0 || p_num >= 1000) {
            printf("%d\n", c);
            continue;
        }

        memset(dp, 0, sizeof(dp));
        for (int w = 1; w <= c; w++) {
            int max_m = (w * p_num) / 1000;
            for (int m = 1; m <= max_m; m++) {
                int k = (m * 1000 + p_num - 1) / p_num;
                if (k > w) continue;
                int nw = w - k + m;
                int val = m + dp[nw];
                if (val > dp[w]) dp[w] = val;
            }
        }

        printf("%d\n", c + dp[c]);
    }
    return 0;
}
