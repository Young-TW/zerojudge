#include <cstdio>
#include <cstdint>
#include <cstring>
#include <algorithm>
using namespace std;

static const int D = 10;
static const int V = 101;            // coordinate values 0..100
static const int NMAX = 200000;
static const int W = (NMAX + 63) / 64; // 3125 words

static uint64_t prefix[D][V][W];     // ~25 MB

static char ibuf[1 << 20];
static int ibufLen = 0, ibufPos = 0;
static int g_eof = 0;
static inline int gc() {
    if (ibufPos == ibufLen) {
        ibufLen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ibufPos = 0;
        if (ibufLen == 0) return -1;
    }
    return ibuf[ibufPos++];
}
static inline int readInt() {
    int c = gc();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = gc();
    if (c == -1) { g_eof = 1; return 0; }
    int sign = 1;
    if (c == '-') { sign = -1; c = gc(); if (c == -1) { g_eof = 1; return 0; } }
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return x * sign;
}

int main() {
    int N = 0;
    while (true) {
        int v0 = readInt();
        if (v0 == -1) break;          // points terminator
        int coord[D];
        coord[0] = v0;
        for (int i = 1; i < D; i++) coord[i] = readInt();
        for (int i = 0; i < D; i++) {
            int v = coord[i];
            prefix[i][v][N >> 6] |= (1ULL << (N & 63));
        }
        N++;
    }
    // prefix-OR sweep: prefix[i][v] |= prefix[i][v-1]
    for (int i = 0; i < D; i++) {
        for (int v = 1; v < V; v++) {
            uint64_t *cur = prefix[i][v], *prev = prefix[i][v - 1];
            for (int k = 0; k < W; k++) cur[k] |= prev[k];
        }
    }

    static uint64_t acc[W];
    while (!g_eof) {
        int L[D], U[D];
        L[0] = readInt();
        if (g_eof) break;
        for (int i = 1; i < D; i++) L[i] = readInt();
        for (int i = 0; i < D; i++) U[i] = readInt();
        (void)readInt();              // -1 separator (or EOF)

        memcpy(acc, prefix[0][U[0]], (size_t)W * 8);
        if (L[0] > 0) {
            uint64_t *lp = prefix[0][L[0] - 1];
            for (int k = 0; k < W; k++) acc[k] &= ~lp[k];
        }
        for (int i = 1; i < D; i++) {
            uint64_t *up = prefix[i][U[i]];
            for (int k = 0; k < W; k++) acc[k] &= up[k];
            if (L[i] > 0) {
                uint64_t *lp = prefix[i][L[i] - 1];
                for (int k = 0; k < W; k++) acc[k] &= ~lp[k];
            }
        }
        long long cnt = 0;
        for (int k = 0; k < W; k++) cnt += __builtin_popcountll(acc[k]);
        printf("%lld\n", cnt);
    }
    return 0;
}
