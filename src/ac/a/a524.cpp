#include <cstdio>
#include <algorithm>

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int a[8];
        for (int i = 0; i < n; i++) a[i] = n - i;
        do {
            for (int i = 0; i < n; i++) printf("%d", a[i]);
            printf("\n");
        } while (std::prev_permutation(a, a + n));
    }
    return 0;
}
