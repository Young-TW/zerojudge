#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double V, R;
    while (cin >> V >> R) {
        double I_mA = (V / R) * 1000.0;
        cout << fixed << setprecision(4) << I_mA << "\n";
    }
    
    return 0;
}
