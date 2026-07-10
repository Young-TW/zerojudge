#include <cstdio>

int n;
int parts[105];
char outbuf[1 << 20];
int outpos = 0;

static inline void flushOut() {
    if (outpos > (1 << 19)) {
        fwrite(outbuf, 1, outpos, stdout);
        outpos = 0;
    }
}

void gen(int remaining, int maxPart, int idx) {
    if (remaining == 0) {
        for (int i = 0; i < idx; i++) {
            if (i) outbuf[outpos++] = ' ';
            int x = parts[i];
            char tmp[4];
            int t = 0;
            while (x) { tmp[t++] = '0' + (x % 10); x /= 10; }
            while (t) outbuf[outpos++] = tmp[--t];
        }
        outbuf[outpos++] = '\n';
        flushOut();
        return;
    }
    int limit = remaining < maxPart ? remaining : maxPart;
    for (int i = limit; i >= 1; i--) {
        parts[idx] = i;
        gen(remaining - i, i, idx + 1);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        outpos = 0;
        gen(n, n, 0);
        fwrite(outbuf, 1, outpos, stdout);
    }
    return 0;
}
