#include <cstdio>
#include <algorithm>
using namespace std;

// Three-Heap Wythoff's Game.
// Move: pick a non-empty subset of the three piles and remove the same
// positive number of stones from each chosen pile.
// Terminal (0,0,0) = player to move loses => P-position.
// Bob (second player) wins exactly on P-positions (losing for the mover).
//
// We compute P/N status by increasing total sum (every move strictly
// decreases the sum). When a position turns out to be a P-position (never
// marked reachable-to-a-P by any smaller position), we reverse-mark every
// position that can move INTO it as N (win=true).  O(N^3) states + cheap
// reverse marking over the ~few-thousand P-positions.

static const int N = 200;
static const int D = N + 1;          // 201
static char win[201 * 201 * 201];    // win[idx]=1 => N-position (mover wins)

static inline int id(int a, int b, int c) { return (a * D + b) * D + c; }

int main() {
    // Process positions in order of increasing sum.
    for (int s = 0; s <= 3 * N; ++s) {
        int alo = s - 2 * N; if (alo < 0) alo = 0;
        int ahi = s;         if (ahi > N) ahi = N;
        for (int a = alo; a <= ahi; ++a) {
            int rem = s - a;                 // b + c
            int blo = rem - N; if (blo < 0) blo = 0;
            int bhi = rem;     if (bhi > N) bhi = N;
            for (int b = blo; b <= bhi; ++b) {
                int c = rem - b;             // 0..N guaranteed
                int cur = id(a, b, c);
                if (win[cur]) continue;      // already N
                // (a,b,c) is a P-position. Reverse-mark predecessors.
                // For each non-empty subset of coords, add d>0 to those coords.
                for (int mask = 1; mask < 8; ++mask) {
                    int ma = (mask & 1) ? a : -1;
                    int mb = (mask & 2) ? b : -1;
                    int mc = (mask & 4) ? c : -1;
                    // max d limited by chosen coords not exceeding N
                    int dmax = N;
                    if (mask & 1) dmax = min(dmax, N - a);
                    if (mask & 2) dmax = min(dmax, N - b);
                    if (mask & 4) dmax = min(dmax, N - c);
                    for (int d = 1; d <= dmax; ++d) {
                        int na = (mask & 1) ? a + d : a;
                        int nb = (mask & 2) ? b + d : b;
                        int nc = (mask & 4) ? c + d : c;
                        win[id(na, nb, nc)] = 1;
                    }
                    (void)ma; (void)mb; (void)mc;
                }
            }
        }
    }

    // Output sorted P-positions a<=b<=c in lexicographic order.
    for (int a = 0; a <= N; ++a)
        for (int b = a; b <= N; ++b)
            for (int c = b; c <= N; ++c)
                if (!win[id(a, b, c)])
                    printf("%d %d %d\n", a, b, c);
    return 0;
}
