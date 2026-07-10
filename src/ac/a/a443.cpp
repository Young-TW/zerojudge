#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

static const int MAXN = 1000005;
static int d[MAXN];        // degrees read
static int cnt[MAXN];      // count per degree value
static int G[MAXN];        // G[k] = number of vertices with degree >= k
static long long S[MAXN];  // prefix sums of sorted-descending degrees

// ---------- fast input ----------
static char ibuf[1 << 16];
static int ibufLen = 0, ibufPos = 0;
static inline int gc() {
    if (ibufPos == ibufLen) {
        ibufLen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ibufPos = 0;
        if (ibufLen == 0) return -1;
    }
    return ibuf[ibufPos++];
}
// read one integer (possibly negative); return false if no token (EOF)
static inline bool readInt(long long &x) {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    if (c == -1) return false;
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    long long v = 0;
    while (c >= '0' && c <= '9') { v = v * 10 + (c - '0'); c = gc(); }
    x = neg ? -v : v;
    return true;
}

int main() {
    long long t;
    while (readInt(t)) {
        int n = (int)t;
        if (n == 0) break;

        bool rangeOK = true;
        long long sum = 0;
        int maxdeg = 0;
        for (int i = 0; i < n; ++i) {
            long long v;
            readInt(v);
            d[i] = (int)v;            // safe: only used when rangeOK
            sum += v;
            if (v < 0 || v > (long long)n - 1) rangeOK = false;
            if (v > maxdeg && v <= n - 1) maxdeg = (int)v;
        }

        // degree out of [0, n-1] -> impossible for simple graph
        // odd sum -> impossible (handshake lemma)
        if (!rangeOK || (sum & 1)) {
            puts("Not possible");
            continue;
        }
        if (n == 1) { // degree must be 0 here
            puts("Possible");
            continue;
        }

        // counting sort: build cnt[0..maxdeg]
        if (maxdeg > n - 1) maxdeg = n - 1;
        memset(cnt, 0, sizeof(int) * (maxdeg + 1));
        for (int i = 0; i < n; ++i) cnt[d[i]]++;

        // suffix counts: G[k] = #{ vertices with degree >= k }
        G[maxdeg] = cnt[maxdeg];
        for (int k = maxdeg - 1; k >= 0; --k) G[k] = G[k + 1] + cnt[k];

        // prefix sums of sorted-descending degrees (build directly from cnt)
        S[0] = 0;
        long long run = 0;
        int pos = 0;
        for (int j = maxdeg; j >= 0; --j) {
            int c = cnt[j];
            for (int r = 0; r < c; ++r) {
                run += j;
                S[++pos] = run;
            }
        }
        // pos == n

        // Erdos-Gallai check, O(n)
        // For each k=1..n:
        //   2*S[k] <= k*(k-1) + k*(G[k]-p) + L[k] + S[p]
        // where p = min(k, G[k]), L[k] = sum of degrees of vertices with degree < k
        bool ok = true;
        long long L = 0; // L[0] = 0; L[k] = L[k-1] + (k-1)*cnt[k-1]
        for (int k = 1; k <= n && ok; ++k) {
            if (k - 1 <= maxdeg) L += (long long)(k - 1) * cnt[k - 1];
            int Gk = (k <= maxdeg) ? G[k] : 0;
            int p = (k < Gk) ? k : Gk;       // min(k, Gk)
            long long Sp = S[p];
            long long lhs = 2 * S[k];
            long long rhs = (long long)k * (k - 1) + (long long)k * (Gk - p) + L + Sp;
            if (lhs > rhs) ok = false;
        }

        puts(ok ? "Possible" : "Not possible");
    }
    return 0;
}
