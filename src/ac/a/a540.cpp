#include <cstdio>

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        long long best = 0, cur = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            cur += x;
            if (cur < 0) cur = 0;
            if (cur > best) best = cur;
        }
        if (best > 0)
            printf("The maximum winning streak is %lld.\n", best);
        else
            printf("Losing streak.\n");
    }
    return 0;
}
