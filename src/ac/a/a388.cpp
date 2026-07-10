#include <cstdio>

int main() {
    long long f[64];
    f[0] = 1; f[1] = 2; f[2] = 4;
    for (int i = 3; i < 64; i++) f[i] = f[i-1] + f[i-2] + f[i-3];
    long long p2[64];
    p2[0] = 1;
    for (int i = 1; i < 64; i++) p2[i] = p2[i-1] * 2;
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        printf("%lld\n", p2[n] - f[n]);
    }
    return 0;
}
