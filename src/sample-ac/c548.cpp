#include <cstdio>
#include <vector>

int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) == 2) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        
        std::vector<int> firstPos(k, -1);
        firstPos[0] = n;
        
        long long sum = 0;
        int start = -1, end = -1;
        for (int i = n - 1; i >= 0; i--) {
            sum = (sum + a[i] % k) % k;
            int s = (int)sum;
            if (firstPos[s] != -1) {
                start = i;
                end = firstPos[s] - 1;
                break;
            }
            firstPos[s] = i;
        }
        
        if (start == -1) {
            printf("0\n");
        } else {
            printf("%d\n", end - start + 1);
            for (int i = start; i <= end; i++) {
                if (i > start) printf(" ");
                printf("%d", i + 1);
            }
            printf("\n");
        }
    }
    return 0;
}
