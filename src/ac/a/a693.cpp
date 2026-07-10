#include <cstdio>

int main() {
    int n, m;
    static long long pre[100005];
    while (scanf("%d %d", &n, &m) == 2) {
        pre[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            pre[i] = pre[i - 1] + x;
        }
        for (int i = 0; i < m; ++i) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", pre[r] - pre[l - 1]);
        }
    }
    return 0;
}
