#include <stdio.h>

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int count[101] = {0};
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            count[x]++;
        }
        bool first = true;
        for (int i = 1; i <= 100; ++i) {
            for (int j = 0; j < count[i]; ++j) {
                if (!first) {
                    printf(" ");
                }
                printf("%d", i);
                first = false;
            }
        }
        printf("\n");
    }
    return 0;
}
