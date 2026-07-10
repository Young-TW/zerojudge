#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int T;
    while (scanf("%d", &T) == 1) {
        while (T--) {
            int m, n;
            scanf("%d %d", &m, &n);
            vector<vector<int>> v(m, vector<int>(n));
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) scanf("%d", &v[i][j]);
                sort(v[i].begin(), v[i].end());
            }
            // process sets in lexicographic order so any chain is processed in order
            vector<int> idx(m);
            for (int i = 0; i < m; i++) idx[i] = i;
            sort(idx.begin(), idx.end(), [&](int a, int b) {
                return v[a] < v[b];
            });
            vector<int> dp(m, 1);
            int best = 1;
            for (int ii = 0; ii < m; ii++) {
                int i = idx[ii];
                for (int jj = 0; jj < ii; jj++) {
                    int j = idx[jj];
                    bool ok = true;
                    for (int c = 0; c < n; c++) {
                        if (v[j][c] >= v[i][c]) { ok = false; break; }
                    }
                    if (ok && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
                }
                if (dp[i] > best) best = dp[i];
            }
            printf("%d\n", best);
        }
    }
    return 0;
}
