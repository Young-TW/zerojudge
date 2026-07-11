#include <cstdio>

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        long long M0 = -2000000000000000000LL;
        long long M1 = 2000000000000000000LL;
        for (int i = 0; i < N; ++i) {
            long long c;
            int d;
            scanf("%lld %d", &c, &d);
            if (d == 0) {
                if (c > M0) M0 = c;
            } else {
                if (c < M1) M1 = c;
            }
        }
        long long ans = M1 - M0;
        if (ans > 0) {
            printf("%lld\n", ans);
        } else {
            printf("I am a robot.\n");
        }
    }
    return 0;
}
