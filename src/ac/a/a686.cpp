#include <cstdio>
using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            long long x, y, z;
            if (scanf("%lld %lld %lld", &x, &y, &z) != 3) return 0;
            if (y > z) {
                long long num = x - z;
                long long den = y - z;
                long long d;
                if (num <= 0) d = 1;
                else d = (num + den - 1) / den;
                printf("%lld\n", d);
            } else {
                if (x <= y) printf("1\n");
                else printf("Poor Snail\n");
            }
        }
    }
    return 0;
}
