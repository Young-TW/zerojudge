#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    double gx, gy, dx, dy;
    while (cin >> n >> gx >> gy >> dx >> dy) {
        bool escaped = false;
        double ans_x = 0.0, ans_y = 0.0;
        for (int i = 0; i < n; ++i) {
            double hx, hy;
            cin >> hx >> hy;
            if (!escaped) {
                double dg_sq = (hx - gx) * (hx - gx) + (hy - gy) * (hy - gy);
                double dd_sq = (hx - dx) * (hx - dx) + (hy - dy) * (hy - dy);
                if (4.0 * dg_sq <= dd_sq + 1e-9) {
                    escaped = true;
                    ans_x = hx;
                    ans_y = hy;
                }
            }
        }
        if (escaped) {
            cout << "The gopher can escape through the hole at (" 
                 << fixed << setprecision(3) << ans_x << "," 
                 << ans_y << ").\n";
        } else {
            cout << "The gopher cannot escape.\n";
        }
    }
    return 0;
}
