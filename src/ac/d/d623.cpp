#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        if (abs(a) < 1e-9 && abs(b) < 1e-9 && abs(c) < 1e-9 && abs(d) < 1e-9) {
            break;
        }
        
        double det = a * d - b * c;
        if (abs(det) < 1e-9) {
            cout << "cheat!\n";
        } else {
            double r1 = d / det;
            double r2 = -b / det;
            double r3 = -c / det;
            double r4 = a / det;
            
            if (abs(r1) < 1e-9) r1 = 0.0;
            if (abs(r2) < 1e-9) r2 = 0.0;
            if (abs(r3) < 1e-9) r3 = 0.0;
            if (abs(r4) < 1e-9) r4 = 0.0;
            
            cout << fixed << setprecision(5);
            cout << r1 << " " << r2 << "\n";
            cout << r3 << " " << r4 << "\n";
        }
    }
    
    return 0;
}
