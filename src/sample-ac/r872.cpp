#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100000;
int f[MAXN + 1];
int ans[MAXN + 1];

int main() {
    f[1] = 1;
    for (int d = 1; d <= MAXN; ++d) {
        for (int k = 2; d * k <= MAXN; ++k) {
            f[d * k] += f[d];
        }
    }

    int n;
    while (scanf("%d", &n) == 1) {
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < n; ++i) {
            int a;
            scanf("%d", &a);
            for (int k = 1; a * k <= MAXN; ++k) {
                ans[a * k] += f[k];
            }
        }

        int q;
        if (scanf("%d", &q) != 1) break;
        for (int i = 0; i < q; ++i) {
            int l;
            scanf("%d", &l);
            printf("%d", ans[l]);
            if (i < q - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
