#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double x1, y1, x2, y2, x3, y3;
    const double PI = 3.141592653589793;
    
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        double a = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
        double b = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
        double c = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        
        double A = fabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0;
        
        double R = (a * b * c) / (4.0 * A);
        double C = 2.0 * PI * R;
        
        cout << fixed << setprecision(2) << C << "\n";
    }
    
    return 0;
}
