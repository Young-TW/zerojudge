#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

// Fast input
static const int BUFSZ = 1 << 22;
static char ibuf[BUFSZ];
static int ipos = 0, ilen = 0;
static inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, BUFSZ, stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}
// read a non-negative integer; returns false on EOF before any digit
static bool readInt(long long &out) {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    if (c == -1) return false;
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    long long v = 0;
    while (c >= '0' && c <= '9') { v = v * 10 + (c - '0'); c = gc(); }
    out = neg ? -v : v;
    return true;
}

int main() {
    long long N;
    // Loop over possibly multiple datasets (robust to multi-EOF); typically one.
    while (readInt(N)) {
        if (N < 0) N = 0;
        // read N chars of 0/1 (skip any whitespace/CR)
        vector<unsigned char> r((size_t)N); // needed flip parity: 1 if char=='0'
        long long got = 0;
        while (got < N) {
            int c = gc();
            if (c == -1) break;
            if (c == '0') { r[(size_t)got++] = 1; }
            else if (c == '1') { r[(size_t)got++] = 0; }
            // else skip (spaces, \r, \n)
        }
        // fill any missing (shouldn't happen) as '1' already-slow -> r=0
        for (; got < N; ++got) r[(size_t)got] = 0;

        if (N == 0) { printf("0\n"); continue; }

        // DP from p = N down to 1. f(N+1) = 0 fixed.
        // dp[b] for current p+1 boundary carried as (dpNext0,dpNext1).
        // p uses index N-1 (0-based) down to 0.
        long long INF = (long long)4e18;
        // initialize for p = N (last), boundary f(N+1)=0
        // dp[b] = (b ^ r[N]) + (b ^ 0)
        long long cur0, cur1;
        {
            unsigned char rp = r[(size_t)(N - 1)];
            cur0 = (0 ^ rp) + 0;      // b=0
            cur1 = (1 ^ rp) + 1;      // b=1
        }
        for (long long p = N - 1; p >= 1; --p) {
            unsigned char rp = r[(size_t)(p - 1)];
            // transition min for choosing b, next states cur0(=dp[p+1][0]) cur1
            // dp[p][b] = (b^rp) + min( (b^0)+cur0, (b^1)+cur1 )
            long long b0trans = (0 ^ 0) + cur0;
            long long b0t2 = (0 ^ 1) + cur1;
            if (b0t2 < b0trans) b0trans = b0t2;
            long long new0 = (0 ^ rp) + b0trans;

            long long b1trans = (1 ^ 0) + cur0;
            long long b1t2 = (1 ^ 1) + cur1;
            if (b1t2 < b1trans) b1trans = b1t2;
            long long new1 = (1 ^ rp) + b1trans;

            cur0 = new0; cur1 = new1;
        }
        long long ans = cur0 < cur1 ? cur0 : cur1;
        printf("%lld\n", ans);
    }
    return 0;
}
