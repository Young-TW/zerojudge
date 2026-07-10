#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 3005;
struct Act {
    int s, e, v;
};

Act a[MAXN];
long long dp[MAXN];
int N;

int main() {
    while (scanf("%d", &N) == 1) {
        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &a[i].s, &a[i].e, &a[i].v);
        }
        sort(a, a + N, [](const Act& x, const Act& y) {
            return x.e < y.e;
        });
        // dp[i] = max value considering first i activities (a[0..i-1])
        dp[0] = 0;
        for (int i = 1; i <= N; i++) {
            // current activity a[i-1]; find largest j in [1,i-1] with a[j-1].e <= a[i-1].s
            int lo = 1, hi = i - 1, j = 0;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (a[mid - 1].e <= a[i - 1].s) { j = mid; lo = mid + 1; }
                else hi = mid - 1;
            }
            long long take = (long long)a[i - 1].v + dp[j];
            dp[i] = dp[i - 1] > take ? dp[i - 1] : take;
        }
        printf("%lld\n", dp[N]);
    }
    return 0;
}
