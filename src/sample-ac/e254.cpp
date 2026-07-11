#include <cstdio>
#include <algorithm>

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        long long n, m;
        if (scanf("%lld %lld", &n, &m) != 2) break;
        long long ans = 0;
        if (n > m) std::swap(n, m);
        for (long long l = 1, r; l <= n; l = r + 1) {
            long long q1 = n / l;
            long long q2 = m / l;
            r = std::min(n / q1, m / q2);
            long long sum_d = (l + r) * (r - l + 1) / 2;
            ans += sum_d * q1 * q2;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
