#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double p, q, r, s, t, u;
    while (cin >> p >> q >> r >> s >> t >> u) {
        double L = 0.0, R = 1.0;
        auto f = [&](double x) {
            return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
        };
        
        if (f(0.0) < -1e-7 || f(1.0) > 1e-7) {
            cout << "No solution\n";
        } else {
            for (int i = 0; i < 100; ++i) {
                double mid = (L + R) / 2.0;
                if (f(mid) > 0.0) {
                    L = mid;
                } else {
                    R = mid;
                }
            }
            cout << fixed << setprecision(4) << (L + R) / 2.0 << "\n";
        }
    }
    return 0;
}
