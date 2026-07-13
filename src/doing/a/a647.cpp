#include <cstdio>
using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            int m, p;
            scanf("%d %d", &m, &p);
            long long num = (long long)(p - m) * 100;
            bool dispose = (num >= 10LL * m) || (num <= -7LL * m);
            double x = (double)(p - m) * 100.0 / (double)m;
            printf("%6.2f%% %s\n", x, dispose ? "dispose" : "keep");
        }
    }
    return 0;
}
