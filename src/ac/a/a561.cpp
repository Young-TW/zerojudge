#include <cstdio>
#include <cstdint>
#include <cstddef>

static const int MAXV = 10000000;                 // values are 0 … 9,999,999
static unsigned char bits[(MAXV + 7) >> 3];       // 10,000,000 bits = 1,250,000 bytes

// ---------- fast input ----------
static const std::size_t BUFSIZE = 1 << 20;       // 1 MB buffer
static unsigned char ibuf[BUFSIZE];
static std::size_t ilen = 0, ipos = 0;

inline int getChar() {
    if (ipos >= ilen) {
        ilen = fread(ibuf, 1, BUFSIZE, stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

inline bool readInt(int &out) {
    int c = getChar();
    if (c == -1) return false;
    while (c < '0' || c > '9') {          // skip non‑digit characters
        c = getChar();
        if (c == -1) return false;
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getChar();
    }
    out = x;
    return true;
}
// --------------------------------

int main() {
    int n;
    if (!readInt(n)) return 0;            // no input

    for (int i = 0; i < n; ++i) {
        int v;
        readInt(v);                       // numbers are guaranteed to be valid
        bits[v >> 3] |= static_cast<unsigned char>(1u << (v & 7));
    }

    int idx = 0;                          // position in sorted order (0‑based)
    bool first = true;
    for (int v = 0; v < MAXV; ++v) {
        if (bits[v >> 3] & (1u << (v & 7))) {
            if (idx % 10 == 0) {
                if (!first) putchar(' ');
                first = false;
                printf("%d", v);
            }
            ++idx;
        }
    }
    putchar('\n');
    return 0;
}
