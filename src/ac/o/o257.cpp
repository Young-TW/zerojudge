#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    int a, b;
    long long w;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    while (std::cin >> N) {
        if (N <= 0) {
            std::cout << 0 << '\n';
            continue;
        }
        std::vector<Interval> seg(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> seg[i].a >> seg[i].b >> seg[i].w;
        }
        // sort by ending time (inclusive)
        std::sort(seg.begin(), seg.end(),
                  [](const Interval& x, const Interval& y) {
                      if (x.b != y.b) return x.b < y.b;
                      return x.a < y.a;
                  });

        std::vector<int> ends(N);
        for (int i = 0; i < N; ++i) ends[i] = seg[i].b;

        std::vector<long long> dp(N + 1, 0); // dp[0]=0
        for (int i = 1; i <= N; ++i) {
            const Interval& cur = seg[i - 1];
            // number of intervals whose end < cur.a
            int pos = std::lower_bound(ends.begin(), ends.end(), cur.a) - ends.begin();
            long long take = dp[pos] + cur.w;
            long long skip = dp[i - 1];
            dp[i] = (take > skip) ? take : skip;
        }
        std::cout << dp[N] << '\n';
    }
    return 0;
}
