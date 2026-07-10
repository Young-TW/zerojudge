#include <cstdio>
#include <algorithm>
using namespace std;

long long pow10[20];

int main() {
    pow10[0] = 1;
    for (int i = 1; i < 20; i++) pow10[i] = pow10[i-1] * 10;

    int T;
    if (scanf("%d", &T) != 1) return 0;

    static long long minN[18][18], maxN[18][18];
    static bool found[18][18];

    for (int p = 1; p <= 17; p++) {
        for (int q = 1; q <= 17; q++) {
            int m = (p < q) ? p : q;
            long long mod = 1LL << q;
            long long sMin = -1, sMax = -1;
            int total = 1 << m;
            for (int mask = 0; mask < total; mask++) {
                long long s = 0;
                for (int i = 0; i < m; i++) {
                    int d = ((mask >> i) & 1) ? 2 : 1;
                    s = s * 10 + d;
                }
                if (s % mod == 0) {
                    if (sMin == -1) sMin = s;
                    sMax = s;
                }
            }
            if (sMin == -1) {
                found[p][q] = false;
            } else {
                found[p][q] = true;
                int L = p - m;
                long long prefix1 = (pow10[L] - 1) / 9;
                long long prefix2 = 2 * prefix1;
                minN[p][q] = prefix1 * pow10[m] + sMin;
                maxN[p][q] = prefix2 * pow10[m] + sMax;
            }
        }
    }

    for (int t = 1; t <= T; t++) {
        int p, q;
        scanf("%d %d", &p, &q);
        printf("Case %d: ", t);
        if (!found[p][q]) {
            printf("impossible\n");
        } else if (minN[p][q] == maxN[p][q]) {
            printf("%lld\n", minN[p][q]);
        } else {
            printf("%lld %lld\n", minN[p][q], maxN[p][q]);
        }
    }
    return 0;
}
