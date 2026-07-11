#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double S;
    while (cin >> S) {
        double r1 = sqrt(3.0) / 2.0 * S;
        double r2 = (2.0 * sqrt(3.0) - 3.0) * S;
        double r3 = sqrt(3.0) / 4.0 * S;
        double r4 = (6.0 * sqrt(7.0) - 7.0 * sqrt(3.0)) / 10.0 * S;
        
        cout << fixed << setprecision(10) << r1 << " " << r2 << " " << r3 << " " << r4 << "\n";
    }
    
    return 0;
}
