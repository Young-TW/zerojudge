#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cstring>
using namespace std;

struct Point {
    int x, y;
};

double dist(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Point> islands(n);
        for (int i = 0; i < n; ++i) {
            cin >> islands[i].x >> islands[i].y;
        }

        vector<vector<double>> dp(1 << n, vector<double>(n, 1e18));
        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = 0;
        }

        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int last = 0; last < n; ++last) {
                if (!(mask & (1 << last))) continue;
                for (int next = 0; next < n; ++next) {
                    if (mask & (1 << next)) continue;
                    int new_mask = mask | (1 << next);
                    dp[new_mask][next] = min(dp[new_mask][next], dp[mask][last] + dist(islands[last], islands[next]));
                }
            }
        }

        double ans = 1e18;
        int full_mask = (1 << n) - 1;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, dp[full_mask][i]);
        }

        cout << fixed << setprecision(2) << ans << '\n';
    }

    return 0;
}
