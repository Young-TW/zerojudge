#include <cstdio>
#include <algorithm>
using namespace std;

static char buf[1 << 20];
static int bufLen = 0, bufPos = 0;

static inline int gc() {
    if (bufPos == bufLen) {
        bufLen = fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen == 0) return EOF;
    }
    return buf[bufPos++];
}

static inline long long readLL() {
    long long x = 0; int c = gc();
    while (c < '0' || c > '9') { if (c == EOF) return -1; c = gc(); }
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return x;
}

int main() {
    long long T = readLL();
    while (T--) {
        long long N = readLL();
        long long K = readLL();
        int* a = new int[N];
        for (int i = 0; i < N; i++) a[i] = (int)readLL();
        sort(a, a + N);
        long long M = N * (N - 1) / 2;
        long long Kp = M - K + 1; // K'-th smallest = K-th largest
        long long lo = 0, hi = (long long)a[N-1] - a[0];
        while (lo < hi) {
            long long mid = (lo + hi) / 2;
            long long cnt = 0;
            int j = 0;
            for (int i = 0; i < N; i++) {
                while (j < N && (long long)a[j] - a[i] <= mid) j++;
                cnt += j - i - 1;
            }
            if (cnt >= Kp) hi = mid;
            else lo = mid + 1;
        }
        printf("%lld\n", lo);
        delete[] a;
    }
    return 0;
}
