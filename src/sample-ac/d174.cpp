#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const double PI = acos(-1.0);
    double D, V;
    
    while (cin >> D >> V && (D != 0.0 || V != 0.0)) {
        double volume_diff = D * D * D - (6.0 * V) / PI;
        double d = cbrt(volume_diff);
        cout << fixed << setprecision(3) << d << "\n";
    }
    
    return 0;
}
