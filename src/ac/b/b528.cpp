#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double Y;
    const double PI = acos(-1.0);
    const double max_Y = sin(1.0);
    const double min_Y = sin(-1.0);
    
    while (cin >> Y) {
        if (Y < min_Y - 1e-6 || Y > max_Y + 1e-6) {
            cout << "FAIL!\n";
            continue;
        }
        
        if (Y > max_Y) Y = max_Y;
        if (Y < min_Y) Y = min_Y;
        
        double W = asin(Y);
        if (W > 1.0) W = 1.0;
        if (W < -1.0) W = -1.0;
        
        double Z = acos(W);
        double X = Z * 180.0 / PI;
        
        cout << fixed << setprecision(2) << X << "\n";
    }
    
    return 0;
}
