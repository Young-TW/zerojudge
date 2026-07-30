#include <stdio.h>

// c489: N pieces, K flavors each with M pieces, exactly one flavor is deficient
// (appears fewer than M times, at least once). Find that flavor.
// Memory limit 5MB, up to 10^6 numbers, flavor value up to 10^9. No <iostream>.
//
// Method (single pass, O(1) memory):
//   bit-sum: cnt[b] = number of pieces whose value has bit b set.
//   For each complete flavor (appears M times) it contributes a multiple of M
//   to each bit. The deficient flavor F (appears r < M times, r >= 1) makes
//   cnt[b] % M != 0 exactly on the set bits of F.
//   To obtain M without storing everything: only ONE flavor is deficient, so
//   among the first value x0 and the first value != x0 (x1), at least one is
//   complete, hence M = max(freq(x0), freq(x1)).

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        long long cnt[32];
        for (int b = 0; b < 32; ++b) cnt[b] = 0;

        long long x0 = 0, x1 = 0;
        long long c0 = 0, c1 = 0;   // frequencies of x0 and x1
        int have0 = 0, have1 = 0;

        for (int i = 0; i < N; ++i) {
            long long v;
            scanf("%lld", &v);
            long long t = v;
            for (int b = 0; b < 32 && t; ++b) {
                if (t & 1LL) cnt[b]++;
                t >>= 1;
            }
            if (!have0) { x0 = v; have0 = 1; }
            if (v == x0) { c0++; }
            else {
                if (!have1) { x1 = v; have1 = 1; }
                if (v == x1) c1++;
            }
        }

        if (!have1) {
            // Only one distinct flavor overall -> that one is the deficient one.
            printf("%lld\n", x0);
            continue;
        }

        long long M = (c0 > c1) ? c0 : c1;

        long long F = 0;
        if (M > 0) {
            for (int b = 0; b < 32; ++b) {
                if (cnt[b] % M != 0) F |= (1LL << b);
            }
        }
        printf("%lld\n", F);
    }
    return 0;
}
