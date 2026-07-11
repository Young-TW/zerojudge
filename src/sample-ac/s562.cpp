#include <cstdio>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        unsigned int n;
        if (scanf("%u", &n) != 1) break;
        printf("%d\n", __builtin_popcount(n));
    }
    return 0;
}
