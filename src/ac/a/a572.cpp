#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        vector<long long> a(N);
        for (int i = 0; i < N; i++) scanf("%lld", &a[i]);
        vector<long long> sorted = a;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        int m = (int)sorted.size();
        vector<long long> tree(m + 1, 0);
        long long ans = 0;
        for (int i = 0; i < N; i++) {
            int r = (int)(lower_bound(sorted.begin(), sorted.end(), a[i]) - sorted.begin()) + 1;
            long long best = 0;
            for (int j = r - 1; j > 0; j -= j & -j) best = max(best, tree[j]);
            long long cur = best + a[i];
            for (int j = r; j <= m; j += j & -j) tree[j] = max(tree[j], cur);
            ans = max(ans, cur);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
