#include <cstdio>

static char buf[1 << 25];
static int bufLen = 0, bufPos = 0;

inline int gc() {
    if (bufPos == bufLen) {
        bufLen = fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen == 0) return EOF;
    }
    return buf[bufPos++];
}

inline int readInt() {
    int x = 0, c = gc();
    bool neg = false;
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return 0;
        c = gc();
    }
    if (c == '-') { neg = true; c = gc(); }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return neg ? -x : x;
}

int main() {
    int n = readInt();
    unsigned ones = 0, twos = 0;
    for (int i = 0; i < n; i++) {
        unsigned x = (unsigned)readInt();
        twos |= ones & x;
        ones ^= x;
        unsigned threes = ones & twos;
        ones &= ~threes;
        twos &= ~threes;
    }
    printf("%d\n", (int)ones);
    return 0;
}
