#include <cstdio>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        putchar(__builtin_parity(n) ? '-' : '+');
        putchar('\n');
    }
    return 0;
}
