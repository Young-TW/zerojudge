#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    const int NEG_INF = -1000000000;          // sufficiently small

    while (T--) {
        int N;
        scanf("%d", &N);
        std::vector<int> a(N);
        int maxVal = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &a[i]);
            if (a[i] > maxVal) maxVal = a[i];
        }

        std::vector<int> best(maxVal + 1, NEG_INF);
        int dp = 0;                           // dp for the current prefix

        for (int i = 0; i < N; ++i) {
            int v = a[i];
            if (best[v] != NEG_INF) {
                int cand = best[v] + 1;
                if (cand > dp) dp = cand;    // take interval ending at i
            }
            // keep best[v] up‑to‑date
            if (dp > best[v]) best[v] = dp;
        }

        printf("%d\n", dp);
    }
    return 0;
}
