#include <cstdio>

const int MOD = 10007;
int pow2[500001];

int main() {
    pow2[0] = 1;
    for (int i = 1; i <= 500000; i++) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
    }
    int L;
    while (scanf("%d", &L) == 1) {
        printf("%d\n", pow2[L / 2]);
    }
    return 0;
}
