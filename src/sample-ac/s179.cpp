#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<long long> P(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int w;
            cin >> w;
            P[i] = P[i - 1] + w;
        }
        for (int i = 0; i < m; ++i) {
            int l, r, a, b;
            cin >> l >> r >> a >> b;
            long long target = 1LL * a * P[r] + 1LL * b * P[l - 1];
            int lo = l, hi = r, ans = r;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (1LL * (a + b) * P[mid] >= target) {
                    ans = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
