#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

static const int INBUF = 1 << 16;
static char inbuf[INBUF];
static int inpos = 0, inlen = 0;

static inline int gc() {
    if (inpos == inlen) {
        inlen = (int)fread(inbuf, 1, INBUF, stdin);
        inpos = 0;
        if (inlen == 0) return -1;
    }
    return inbuf[inpos++];
}

static inline bool readInt(int &x) {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    if (c == -1) return false;
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    if (neg) x = -x;
    return true;
}

static const int OUTBUF = 1 << 16;
static char outbuf[OUTBUF];
static int outpos = 0;

static inline void flushOut() {
    if (outpos) { fwrite(outbuf, 1, outpos, stdout); outpos = 0; }
}
static inline void pc(char c) {
    if (outpos == OUTBUF) flushOut();
    outbuf[outpos++] = c;
}
static inline void writeInt(int x) {
    if (x < 0) { pc('-'); x = -x; }
    char tmp[12];
    int t = 0;
    if (x == 0) tmp[t++] = '0';
    while (x) { tmp[t++] = (char)('0' + x % 10); x /= 10; }
    while (t) pc(tmp[--t]);
}

int main() {
    int n;
    const int MAXN = 1000000;
    int *a = (int*)malloc(sizeof(int) * (size_t)MAXN);
    bool firstCase = true;
    while (readInt(n)) {
        if (n < 0) n = 0;
        if (n > MAXN) n = MAXN;
        for (int i = 0; i < n; i++) readInt(a[i]);
        sort(a, a + n);
        if (!firstCase) pc('\n');
        firstCase = false;
        for (int i = 0; i < n; i++) {
            if (i) pc(' ');
            writeInt(a[i]);
        }
    }
    flushOut();
    free(a);
    return 0;
}
