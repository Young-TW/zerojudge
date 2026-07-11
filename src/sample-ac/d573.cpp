#include <cstdio>

int group[100005];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++i) {
            int g, p;
            scanf("%d %d", &g, &p);
            for (int j = 0; j < p; ++j) {
                int k;
                scanf("%d", &k);
                group[k] = g;
            }
        }
        int y;
        scanf("%d", &y);
        printf("%d\n", group[y]);
    }
    return 0;
}
