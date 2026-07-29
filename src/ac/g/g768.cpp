// g768 - 蝸牛老師的雪碧
// Self-derived solution.
// Need a<b, both multiples of N, arithmetic step N: a+(a+N)+...+b = M.
// Let a=N*x, b=N*y (x<y). Sum = N*(y-x+1)*(x+y)/2 = M  => 2M = N*k*s,
// k=y-x+1>=2, s=x+y, with x=(s-k+1)/2, y=(s+k-1)/2 integers => k,s opposite parity.
// Q = 2M/N must be an even integer for a valid (k,s) split (odd Q forces both k,s odd).
// Q even integer  <=>  N | M.  A valid witness: x=1-c, y=c where c=M/N
//   => a = N-M, b = M (k=2c terms, s=1, sum = N*c = M). Always in range and a<b.
// Hence: if N|M print (N-M) M else -1.  O(1) per query.
#include <cstdio>
#include <cstring>

static char ibuf[1 << 25];
static int ipos, ilen;
static inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}
static inline long long readLL() {
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return -1000000000000000000LL; // EOF sentinel
        c = gc();
    }
    long long sign = 1, x = 0;
    if (c == '-') { sign = -1; c = gc(); }
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return x * sign;
}

static char obuf[1 << 25];
static int opos;
static inline void flushOut() { fwrite(obuf, 1, opos, stdout); opos = 0; }
static inline void putLL(long long v) {
    if (opos > (1 << 25) - 64) flushOut();
    if (v < 0) { obuf[opos++] = '-'; v = -v; }
    char tmp[24]; int t = 0;
    if (v == 0) tmp[t++] = '0';
    while (v) { tmp[t++] = char('0' + v % 10); v /= 10; }
    while (t) obuf[opos++] = tmp[--t];
}

int main() {
    long long T = readLL();
    if (T < 0) return 0;
    for (long long i = 0; i < T; i++) {
        long long N = readLL();
        long long M = readLL();
        if (N <= -1000000000000000000LL || M <= -1000000000000000000LL) break;
        if (opos > (1 << 25) - 64) flushOut();
        if (M % N == 0) {
            putLL(N - M);
            obuf[opos++] = ' ';
            putLL(M);
        } else {
            obuf[opos++] = '-'; obuf[opos++] = '1';
        }
        obuf[opos++] = '\n';
    }
    flushOut();
    return 0;
}
