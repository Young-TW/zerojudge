#include <cstdio>

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int c1 = 0, c2 = 0, c3 = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            if (x == 1) {
                c1++;
            } else if (x == 2) {
                c2++;
            } else {
                c3++;
            }
        }
        
        bool first = true;
        for (int i = 0; i < c1; ++i) {
            if (!first) putchar(' ');
            putchar('1');
            first = false;
        }
        for (int i = 0; i < c2; ++i) {
            if (!first) putchar(' ');
            putchar('2');
            first = false;
        }
        for (int i = 0; i < c3; ++i) {
            if (!first) putchar(' ');
            putchar('3');
            first = false;
        }
        putchar('\n');
    }
    return 0;
}
