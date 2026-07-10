#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
using namespace std;

static char inbuf[1 << 20];
static int inLen = 0, inPos = 0;

static inline int gc() {
    if (inPos == inLen) {
        inLen = (int)fread(inbuf, 1, sizeof(inbuf), stdin);
        inPos = 0;
        if (inLen == 0) return -1;
    }
    return inbuf[inPos++];
}

static inline long long readLL() {
    int c = gc();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = gc();
    if (c == -1) return 0;
    bool neg = (c == '-');
    if (neg) c = gc();
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

int main() {
    int N = (int)readLL();
    while (N-- > 0) {
        int R = (int)readLL();
        int C = (int)readLL();
        vector<long long> rowSum(R, 0), colSum(C, 0);
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                long long v = readLL();
                rowSum[r] += v;
                colSum[c] += v;
            }
        }
        long long total = 0;
        for (int r = 0; r < R; r++) total += rowSum[r];

        long long acc = 0;
        int bestRow = 0;
        for (int r = 0; r < R; r++) {
            acc += rowSum[r];
            if (acc * 2 >= total) { bestRow = r; break; }
        }
        long long acc2 = 0;
        int bestCol = 0;
        for (int c = 0; c < C; c++) {
            acc2 += colSum[c];
            if (acc2 * 2 >= total) { bestCol = c; break; }
        }

        long long cost = 0;
        for (int r = 0; r < R; r++) {
            int d = r - bestRow;
            if (d < 0) d = -d;
            cost += rowSum[r] * (long long)d;
        }
        for (int c = 0; c < C; c++) {
            int d = c - bestCol;
            if (d < 0) d = -d;
            cost += colSum[c] * (long long)d;
        }
        cost *= 100;

        printf("%d %d\n%lld\n", bestRow + 1, bestCol + 1, cost);
    }
    return 0;
}
