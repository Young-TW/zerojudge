#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int D, L;
    double PI = 2.0 * acos(0.0);
    
    while (cin >> D >> L) {
        double d = static_cast<double>(D);
        double l = static_cast<double>(L);
        
        double a = l / 2.0;
        double c = d / 2.0;
        double b = sqrt(a * a - c * c);
        
        double area = PI * a * b;
        
        cout << fixed << setprecision(3) << area << "\n";
    }
    
    return 0;
}
