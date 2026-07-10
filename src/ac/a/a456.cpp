#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    bool firstCase = true;
    while (T--) {
        int N;
        scanf("%d", &N);
        // Generate all subsets of {1..N} as bitmasks, sorted by size then lexicographic.
        // Since iterating masks 0..2^N-1 does NOT give lexicographic order within a size,
        // we collect masks grouped by popcount and sort each group lexicographically.
        int total = 1 << N;
        vector<vector<int>> bySize(N + 1);
        for (int m = 0; m < total; m++) {
            bySize[__builtin_popcount(m)].push_back(m);
        }
        // Within each size, sort lexicographically by the sequence of elements.
        // Compare element sequences (ascending elements of the subset).
        for (int s = 0; s <= N; s++) {
            sort(bySize[s].begin(), bySize[s].end(), [N](int a, int b) {
                // Extract elements ascending
                // Lexicographic compare of element lists
                int pa = 0, pb = 0;
                for (int i = 0; i < N; i++) {
                    int bit = 1 << i;
                    int ai = (a & bit) ? 1 : 0;
                    int bi = (b & bit) ? 1 : 0;
                    if (ai != bi) {
                        // The one that has the smaller element present first is "smaller"?
                        // Lexicographic: compare element lists. Smaller element first.
                        // If a has element (i+1) and b doesn't at the first differing position,
                        // then a's list has a smaller element here -> a is smaller.
                        return ai > bi; // ai=1 means present -> smaller element -> a first
                    }
                }
                return false;
            });
        }
        if (!firstCase) printf("\n");
        firstCase = false;
        for (int s = 0; s <= N; s++) {
            for (int m : bySize[s]) {
                printf("{");
                if (s == 0) {
                    printf("0");
                } else {
                    bool firstEl = true;
                    for (int i = 0; i < N; i++) {
                        if (m & (1 << i)) {
                            if (!firstEl) printf(",");
                            printf("%d", i + 1);
                            firstEl = false;
                        }
                    }
                }
                printf("}\n");
            }
        }
    }
    return 0;
}
