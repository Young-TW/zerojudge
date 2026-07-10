#include <cstdio>
#include <cstring>
#include <vector>

static const int MAXV = 10000000;

static unsigned char inbuf[1 << 25];
static int inLen = 0, inPos = 0;

static inline int gc() {
    if (inPos == inLen) {
        inLen = (int)fread(inbuf, 1, sizeof(inbuf), stdin);
        inPos = 0;
        if (inLen == 0) return -1;
    }
    return inbuf[inPos++];
}

static inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    if (c == -1) return -1;
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    static std::vector<bool> seen(MAXV, false);
    int n = readInt();
    if (n < 0) return 0;
    for (int i = 0; i < n; ++i) {
        int x = readInt();
        if (x < 0) break;
        seen[x] = true;
    }
    int idx = 0;
    for (int v = 0; v < MAXV; ++v) {
        if (seen[v]) {
            if (idx % 10 == 0) printf("%d ", v);
            ++idx;
        }
    }
    putchar('\n');
    return 0;
}
