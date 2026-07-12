#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, x;
    double pi = 3.1415926;
    
    while (cin >> n >> x) {
        if (n == 0) break;
        
        x %= 360;
        if (x == 0) {
            cout << "0.0000\n";
            continue;
        }
        
        long long nx = (n % 720) * x;
        nx %= 720;
        
        long long nx1 = ((n + 1) % 720) * x;
        nx1 %= 720;
        
        double rad = pi / 180.0;
        double term1 = sin(nx / 2.0 * rad);
        double term2 = sin(nx1 / 2.0 * rad);
        double term3 = sin(x / 2.0 * rad);
        
        double ans = term1 * term2 / term3;
        cout << fixed << setprecision(4) << ans << "\n";
    }
    
    return 0;
}
