#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

static char buf[1 << 16];
static int bufLen = 0, bufPos = 0;

static inline int gc() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen == 0) return EOF;
    }
    return buf[bufPos++];
}

static bool readll(long long &out) {
    long long x = 0; int c = gc(); int neg = 0;
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = gc();
    if (c == EOF) return false;
    if (c == '-') { neg = 1; c = gc(); }
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    out = neg ? -x : x;
    return true;
}

int main() {
    long long x1, y1, x2, y2, n;
    while (readll(x1)) {
        readll(y1); readll(x2); readll(y2); readll(n);
        int nn = (int)n;
        vector<pair<long long, long long> > v(nn);
        for (int i = 0; i < nn; i++) {
            long long xi, eta;
            readll(xi); readll(eta);
            long long d1x = xi - x1, d1y = eta - y1;
            long long d2x = xi - x2, d2y = eta - y2;
            v[i] = make_pair(d1x * d1x + d1y * d1y, d2x * d2x + d2y * d2y);
        }
        sort(v.begin(), v.end(),
             [](const pair<long long, long long> &p1,
                const pair<long long, long long> &p2) {
                 return p1.first > p2.first;
             });
        long long premax = 0;
        long long ans = v[0].first + 0;
        for (int k = 1; k <= nn; k++) {
            if (v[k - 1].second > premax) premax = v[k - 1].second;
            long long A = (k < nn) ? v[k].first : 0;
            long long cost = A + premax;
            if (cost < ans) ans = cost;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
