#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, k, t;
    while (cin >> a >> k >> t) {
        double A = static_cast<double>(a);
        double K = static_cast<double>(k);
        double T = static_cast<double>(t);
        
        double exp_kt = exp(-K * T);
        double v = (A / K) * (1.0 - exp_kt);
        double acc = A * exp_kt;
        double x = (A / K) * T - (A / (K * K)) * (1.0 - exp_kt);
        
        cout << fixed << setprecision(2);
        cout << "x(" << t << ")=" << x << "\n";
        cout << "v(" << t << ")=" << v << "\n";
        cout << "a(" << t << ")=" << acc << "\n";
    }
    
    return 0;
}
