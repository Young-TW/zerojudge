#include <cstdio>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    const long long NEGINF = (long long)-4e18;
    int n, delta;
    while (scanf("%d %d", &n, &delta) == 2) {
        vector<long long> f(n + 1), g(n + 1);
        deque<int> df, dg;
        long long ans = NEGINF;
        for (int k = 1; k <= n; k++) {
            int x;
            scanf("%d", &x);
            long long ak = x;
            int lo = k - delta;
            while (!df.empty() && df.front() < lo) df.pop_front();
            while (!dg.empty() && dg.front() < lo) dg.pop_front();

            long long gk = NEGINF;
            if (!df.empty()) gk = f[df.front()] - ak;
            long long fk = ak;
            if (!dg.empty()) {
                long long gv = g[dg.front()];
                if (gv != NEGINF) fk = max(fk, gv + ak);
            }

            f[k] = fk;
            g[k] = gk;
            if (fk > ans) ans = fk;
            if (gk != NEGINF && gk > ans) ans = gk;

            while (!df.empty() && f[df.back()] <= fk) df.pop_back();
            df.push_back(k);
            while (!dg.empty() && g[dg.back()] <= gk) dg.pop_back();
            dg.push_back(k);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
