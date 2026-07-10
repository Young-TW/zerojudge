#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int ans[25];        // ans[i] = rank of event i in correct answer
    int corr[25];       // corr[v] = event that has rank v in correct answer
    for (int i = 1; i <= n; i++) {
        scanf("%d", &ans[i]);
        corr[ans[i]] = i;
    }
    int r[25];
    while (scanf("%d", &r[1]) == 1) {
        for (int i = 2; i <= n; i++) scanf("%d", &r[i]);
        int stu[25];    // stu[v] = event that student ranked at position v
        for (int i = 1; i <= n; i++) stu[r[i]] = i;
        int a[25];      // a[i] = correct-rank of the event student placed at position i
        for (int i = 1; i <= n; i++) a[i] = ans[stu[i]];
        int dp[25], best = 0;
        for (int i = 1; i <= n; i++) {
            dp[i] = 1;
            for (int j = 1; j < i; j++)
                if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
            best = max(best, dp[i]);
        }
        printf("%d\n", best);
    }
    return 0;
}
