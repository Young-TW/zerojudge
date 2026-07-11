#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double t1, t2, t3, x1, x3;
    bool has_data = false;
    
    while (cin >> t1 >> t2 >> t3 >> x1 >> x3) {
        double x2 = x3 + (x1 - x3) * (t2 - t3) / (t1 - t3);
        cout << fixed << setprecision(6) << x2 << "\n";
        has_data = true;
    }
    
    if (has_data) {
        cout << "\n*注意浮點數問題(請愛用double)\n";
    }
    
    return 0;
}
