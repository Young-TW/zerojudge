#include <cstdio>
#include <vector>
using namespace std;

static const long long CAP = (long long)4e18;

int main() {
    int n, m;
    long long S;
    if (scanf("%d %d %lld", &n, &m, &S) != 3) return 0;

    vector<int> w(n), v(n);
    int maxw = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &v[i]);
        if (w[i] > maxw) maxw = w[i];
    }
    vector<int> L(m), R(m);
    for (int i = 0; i < m; i++) scanf("%d %d", &L[i], &R[i]);

    vector<long long> cnt(n + 1), sm(n + 1);
    auto compute = [&](int W) -> long long {
        cnt[0] = 0; sm[0] = 0;
        for (int i = 0; i < n; i++) {
            int inc = (w[i] >= W) ? 1 : 0;
            cnt[i + 1] = cnt[i] + inc;
            sm[i + 1] = sm[i] + (inc ? (long long)v[i] : 0LL);
        }
        long long Y = 0;
        for (int i = 0; i < m; i++) {
            long long c = cnt[R[i]] - cnt[L[i] - 1];
            long long s = sm[R[i]] - sm[L[i] - 1];
            Y += c * s;
            if (Y > CAP) { Y = CAP; break; }
        }
        return Y;
    };

    // f(W) = Y is non-increasing in W. W in [0, maxw+1]: f(0)=max, f(maxw+1)=0.
    long long fmax = compute(0);
    long long ans;
    if (fmax <= S) {
        ans = S - fmax;
    } else {
        // f(0) > S, f(maxw+1)=0 < S (S>=1). find largest W with f(W) >= S.
        int low = 0, high = maxw + 1;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (compute(mid) >= S) low = mid;
            else high = mid - 1;
        }
        long long y1 = compute(low);     // >= S
        long long y2 = compute(low + 1); // < S
        ans = y1 - S;
        if (S - y2 < ans) ans = S - y2;
    }

    printf("%lld\n", ans);
    return 0;
}
