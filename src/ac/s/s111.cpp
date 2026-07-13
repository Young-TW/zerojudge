#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

Point pts[2005];
double dp[2005];

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            cin >> pts[i].x >> pts[i].y;
        }
        
        if (n == 1) {
            cout << "0.00\n";
            continue;
        }

        for (int i = 1; i <= n; ++i) {
            dp[i] = 1e18;
        }
        
        dp[1] = dist(pts[1], pts[2]);
        
        for (int k = 2; k < n; ++k) {
            double new_dp_k = 1e18;
            double d_k_k1 = dist(pts[k], pts[k+1]);
            for (int i = 1; i < k; ++i) {
                if (dp[i] < 1e18) {
                    double d_i_k1 = dist(pts[i], pts[k+1]);
                    if (new_dp_k > dp[i] + d_i_k1) {
                        new_dp_k = dp[i] + d_i_k1;
                    }
                }
            }
            for (int i = 1; i < k; ++i) {
                if (dp[i] < 1e18) {
                    dp[i] = dp[i] + d_k_k1;
                }
            }
            dp[k] = new_dp_k;
        }
        
        double ans = 1e18;
        for (int i = 1; i < n; ++i) {
            if (dp[i] < 1e18) {
                ans = min(ans, dp[i] + dist(pts[i], pts[n]));
            }
        }
        
        cout << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
