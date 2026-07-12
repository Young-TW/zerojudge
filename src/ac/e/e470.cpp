#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int MAXN = 1000000;
double H[MAXN + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    H[0] = 0.0;
    for (int i = 1; i <= MAXN; i++) {
        H[i] = H[i - 1] + 1.0 / i;
    }
    
    double gamma = 0.57721566490153286060651209008240243104215933593992;
    
    int n;
    while (cin >> n) {
        double ans;
        if (n <= MAXN) {
            ans = H[n];
        } else {
            double dn = static_cast<double>(n);
            ans = log(dn) + gamma + 1.0 / (2.0 * dn) - 1.0 / (12.0 * dn * dn) + 1.0 / (120.0 * dn * dn * dn * dn);
        }
        cout << fixed << setprecision(3) << ans << "\n";
    }
    
    return 0;
}
