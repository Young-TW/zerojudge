#include <cstdio>

static char buf[1 << 20];
static int bufPos = 0, bufLen = 0;

static inline int getch() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen == 0) return EOF;
    }
    return buf[bufPos++];
}

static inline long long readLL() {
    long long x = 0;
    int c;
    do {
        c = getch();
        if (c == EOF) return -1;
    } while (c < '0' || c > '9');
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getch();
    }
    return x;
}

static inline char readDir() {
    int c;
    do {
        c = getch();
        if (c == EOF) return 0;
    } while (c != 'L' && c != 'R');
    return (char)c;
}

int main() {
    int T = (int)readLL();
    while (T--) {
        long long L = readLL();
        long long n = readLL();
        long long t = readLL();
        int cnt = 0;
        for (long long i = 0; i < n; i++) {
            long long x = readLL();
            char d = readDir();
            long long pos = (d == 'R') ? x + t : x - t;
            if (pos >= 0 && pos <= L) cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
