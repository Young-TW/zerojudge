#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const double g = 9.8;
    const double EPS_V = 1e-6;   // tolerance for velocity
    const double EPS_POS = 1e-6; // tolerance for coordinates
    
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        double v0, D;
        int T;
        cin >> v0 >> D >> T;
        
        double rad = D * M_PI / 180.0;
        double vx = v0 * cos(rad);
        double vy0 = v0 * sin(rad);
        
        double x = vx * T;
        double y = vy0 * T - 0.5 * g * T * T;
        double vy = vy0 - g * T;
        
        if (fabs(x) < EPS_POS) x = 0.0;
        if (fabs(y) < EPS_POS) y = 0.0;
        
        const char* state;
        if (fabs(vy) < EPS_V)       state = "rest";
        else if (vy > 0)            state = "rising";
        else                        state = "falling";
        
        // two spaces before "at" as required by the judge
        printf("x: %.2f, y: %.2f  at %d(s) %s\n", x, y, T, state);
    }
    return 0;
}
