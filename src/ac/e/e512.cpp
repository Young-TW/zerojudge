#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double x1, y1, x2, y2, x3, y3, x4, y4;
    const double eps = 1e-6;
    
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        double ans_x, ans_y;
        if (fabs(x1 - x3) < eps && fabs(y1 - y3) < eps) {
            ans_x = x2 + x4 - x1;
            ans_y = y2 + y4 - y1;
        } else if (fabs(x1 - x4) < eps && fabs(y1 - y4) < eps) {
            ans_x = x2 + x3 - x1;
            ans_y = y2 + y3 - y1;
        } else if (fabs(x2 - x3) < eps && fabs(y2 - y3) < eps) {
            ans_x = x1 + x4 - x2;
            ans_y = y1 + y4 - y2;
        } else {
            ans_x = x1 + x3 - x2;
            ans_y = y1 + y3 - y2;
        }
        cout << fixed << setprecision(3) << ans_x << " " << ans_y << "\n";
    }
    
    return 0;
}
