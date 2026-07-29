// h098 社長的考驗 — self-written by Young.
// Print every 9-digit "password" (each digit 0..9) whose digit sum is 20,
// in lexicographic order, digits separated by single spaces.
#include <cstdio>
int d[9];
int main() {
    // Lexicographic enumeration: iterate d[0] outermost .. d[8] innermost.
    // Prune with remaining-sum bounds so we only emit valid tuples in order.
    // rem = 20 - sum so far, pos = current index; each remaining digit in [0,9].
    // We do an explicit DFS that naturally yields lexicographic order.
    // Use an iterative-safe recursion via function pointer style: simple recursion.
    // (recursion depth is only 9)
    struct R {
        static void rec(int pos, int rem) {
            if (pos == 9) {
                if (rem == 0) {
                    for (int i = 0; i < 9; ++i) {
                        if (i) putchar(' ');
                        putchar('0' + d[i]);
                    }
                    putchar('\n');
                }
                return;
            }
            int left = 9 - pos;           // positions remaining including this one
            for (int v = 0; v <= 9; ++v) {
                int nrem = rem - v;
                if (nrem < 0) break;                 // can't exceed remaining sum
                if (nrem > 9 * (left - 1)) continue; // remaining can't reach nrem
                d[pos] = v;
                rec(pos + 1, nrem);
            }
        }
    };
    R::rec(0, 20);
    return 0;
}
