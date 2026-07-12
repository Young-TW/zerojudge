#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int A, k, t;
    while (cin >> A >> k >> t) {
        long double dA = A;
        long double dk = k;
        long double dt = t;
        
        long double z = sqrtl(dA * dk) * dt;
        long double vT = sqrtl(dA / dk);
        long double v, x, a;
        
        if (z > 30.0L) {
            v = vT;
            x = (z - logl(2.0L)) / dk;
            a = 0.0L;
        } else {
            long double ch = coshl(z);
            v = vT * tanhl(z);
            x = logl(ch) / dk;
            a = dA / (ch * ch);
        }
        
        cout << fixed << setprecision(2);
        cout << "x(" << t << ")=" << x << "\n";
        cout << "v(" << t << ")=" << v << "\n";
        cout << "a(" << t << ")=" << a << "\n";
    }
    
    return 0;
}
