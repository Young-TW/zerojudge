#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>

using namespace std;

int main() {
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        double v0, D;
        int T;
        cin >> v0 >> D >> T;
        double g = 9.8;
        double PI = acos(-1.0);
        double rad = D * PI / 180.0;
        double vx = v0 * cos(rad);
        double vy = v0 * sin(rad);
        double x = vx * T;
        double y = vy * T - 0.5 * g * T * T;
        double vy_T = vy - g * T;
        
        string status;
        if (fabs(vy_T) < 1e-6) status = "rest";
        else if (vy_T > 0) status = "rising";
        else status = "falling";
        
        printf("x: %.2f, y: %.2f  at %d(s) %s\n", x, y, T, status.c_str());
    }
    return 0;
}
