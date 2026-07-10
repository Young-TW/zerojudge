#include <cstdio>
#include <climits>
#include <vector>
#include <set>
#include <utility>
using namespace std;

/*
  a068 - minimize disk swaps given M USB ports.
  Belady's optimal page replacement: evict the disk whose NEXT use is farthest.
  min swaps = max(0, min_misses - M)  (first M misses fill cache without swaps).

  Optimizations for N up to 1e6, M up to 1e4, disk ids in [0, 1e5]:
   - Build next-use array in O(N) using generation-stamped head[] per disk id.
   - O(1) cache membership via generation-stamped ver[] (no hash map).
   - Lazy deletion in the set: on a cache hit we insert the new (nextUse, disk)
     entry and bump usev[d]; stale entries are skipped when they surface during
     eviction. This avoids an erase on every hit.
*/

static const int MAXID = 100001;

static char buf[1 << 25];
static int bufLen = 0, bufPos = 0;

static inline int gc() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen == 0) return -1;
    }
    return buf[bufPos++];
}

static inline int readInt() {
    int c = gc();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
        if (c == -1) return -1;
        c = gc();
    }
    int x = 0, neg = 0;
    if (c == '-') { neg = 1; c = gc(); }
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

// generation-stamped arrays (avoid clearing between test cases)
static int headGen[MAXID], headVal[MAXID];  // for building next-use
static int ver[MAXID], usev[MAXID];         // ver[d]==gen => d cached with usev[d]
static int hg = 0, vg = 0;

int main() {
    int T = readInt();
    if (T < 0) return 0;

    while (T--) {
        int N = readInt();
        int M = readInt();

        vector<int> A(N);
        for (int i = 0; i < N; i++) A[i] = readInt();

        // Build next-use per position, right-to-left, using head[].
        // headVal[d] = smallest index > i with disk d seen so far (from the right).
        vector<int> nxtUse(N);
        hg++;
        for (int i = N - 1; i >= 0; i--) {
            int d = A[i];
            nxtUse[i] = (headGen[d] == hg) ? headVal[d] : INT_MAX;
            headGen[d] = hg;
            headVal[d] = i;
        }

        // Belady with lazy deletion.
        set<pair<int,int>> s; // (nextUse, disk)
        vg++;
        int misses = 0, cached = 0;

        for (int i = 0; i < N; i++) {
            int d = A[i];
            int nu = nxtUse[i];
            if (ver[d] == vg) {
                // hit: lazy update. Old (usev[d], d) becomes stale.
                usev[d] = nu;
                s.insert({nu, d});
            } else {
                misses++;
                if (cached == M) {
                    // evict farthest valid entry
                    while (true) {
                        auto it = prev(s.end());
                        int ud = it->second;
                        if (ver[ud] == vg && usev[ud] == it->first) {
                            ver[ud] = 0;
                            s.erase(it);
                            cached--;
                            break;
                        }
                        s.erase(it); // stale
                    }
                }
                ver[d] = vg;
                usev[d] = nu;
                s.insert({nu, d});
                cached++;
            }
        }

        int swaps = misses - M;
        if (swaps < 0) swaps = 0;
        printf("%d\n", swaps);
    }
    return 0;
}
