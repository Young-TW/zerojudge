#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const char firstDigits[] = "1689";  // outer pair first slot (no leading zero)
static const char midDigits[]   = "01689"; // inner pair slots
static const char centerDigits[]= "018";   // odd-length center slot
static int rot[256];

static long long cnt[64];  // count of strobogrammatic numbers with exactly k digits
static long long cum[64];  // cumulative count up to k digits

int main() {
    rot[(unsigned char)'0'] = '0';
    rot[(unsigned char)'1'] = '1';
    rot[(unsigned char)'6'] = '9';
    rot[(unsigned char)'8'] = '8';
    rot[(unsigned char)'9'] = '6';

    cnt[1] = 3; // 0,1,8
    cnt[2] = 4; // 11,69,88,96
    for (int k = 3; k <= 30; ++k) {
        if (k % 2 == 0) {
            int m = k / 2;          // number of pair positions
            long long c = 4;
            for (int i = 0; i < m - 1; ++i) c *= 5;
            cnt[k] = c;
        } else {
            int m = (k - 1) / 2;    // number of pair positions (+1 center)
            long long c = 4;
            for (int i = 0; i < m - 1; ++i) c *= 5;
            c *= 3;
            cnt[k] = c;
        }
    }
    cum[0] = 0;
    for (int k = 1; k <= 30; ++k) cum[k] = cum[k - 1] + cnt[k];

    long long N;
    while (scanf("%lld", &N) == 1) {
        if (N == 0) break;

        int k = 1;
        while (cum[k] < N) ++k;
        long long offset = N - cum[k - 1] - 1; // 0-indexed within length k

        char half[40];
        int hl = 0;

        if (k == 1) {
            half[hl++] = centerDigits[offset];
        } else if (k % 2 == 0) {
            int m = k / 2;
            long long pw[40];
            pw[m - 1] = 1;
            for (int i = m - 2; i >= 0; --i) pw[i] = pw[i + 1] * 5;
            long long rem = offset;
            for (int i = 0; i < m; ++i) {
                int d = (int)(rem / pw[i]);
                rem %= pw[i];
                half[hl++] = (i == 0) ? firstDigits[d] : midDigits[d];
            }
        } else {
            int m = (k - 1) / 2;
            long long pw5[40];
            pw5[0] = 1;
            for (int i = 1; i <= m; ++i) pw5[i] = pw5[i - 1] * 5;
            long long rem = offset;
            for (int i = 0; i < m; ++i) {
                long long w = pw5[m - 1 - i] * 3;
                int d = (int)(rem / w);
                rem %= w;
                half[hl++] = (i == 0) ? firstDigits[d] : midDigits[d];
            }
            half[hl++] = centerDigits[rem]; // center, 0..2
        }
        half[hl] = 0;

        char full[80];
        int fl = 0;
        for (int i = 0; i < hl; ++i) full[fl++] = half[i];
        if (k % 2 == 0) {
            for (int i = hl - 1; i >= 0; --i) full[fl++] = (char)rot[(unsigned char)half[i]];
        } else {
            for (int i = hl - 2; i >= 0; --i) full[fl++] = (char)rot[(unsigned char)half[i]];
        }
        full[fl] = 0;

        printf("%s\n", full);
    }
    return 0;
}
