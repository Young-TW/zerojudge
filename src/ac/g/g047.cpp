#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <numeric>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double xa, ya, xb, yb, xc, yc;
    while (cin >> xa >> ya >> xb >> yb >> xc >> yc) {
        double Ux = xb - xa;
        double Uy = yb - ya;
        double Vx = xc - xa;
        double Vy = yc - ya;
        
        double Wb = xb * xb + yb * yb - xa * xa - ya * ya;
        double Wc = xc * xc + yc * yc - xa * xa - ya * ya;
        
        double D = 2.0 * (Ux * Vy - Uy * Vx);
        
        if (fabs(D) < 1e-9) {
            cout << "No circumcenter.\n";
        } else {
            double x = (Wb * Vy - Wc * Uy) / D;
            double y = (Ux * Wc - Vx * Wb) / D;
            cout << fixed << setprecision(3) << x << " " << y << "\n";
        }
    }
    
    return 0;
}
