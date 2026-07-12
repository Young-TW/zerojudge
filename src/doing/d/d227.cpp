#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double a;
    const double PI = acos(-1.0);
    
    while (cin >> a) {
        double x = a / 180.0 * PI;
        
        // 利用週期性將 x 縮減至 [-PI, PI] 區間，避免大角度時泰勒展開式收斂過慢及精度損失
        x = fmod(x, 2.0 * PI);
        if (x > PI) {
            x -= 2.0 * PI;
        } else if (x < -PI) {
            x += 2.0 * PI;
        }
        
        double term = x;
        double sum = term;
        int n = 1;
        
        // 泰勒級數展開，直到項的絕對值小於等於 0.01
        while (fabs(term) > 0.01) {
            n += 2;
            term = term * (-x * x) / ((n - 1) * n);
            sum += term;
        }
        
        cout << "N = " << n << "\n";
        cout << fixed << setprecision(6) << sum << "\n";
    }
    
    return 0;
}
