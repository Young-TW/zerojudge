#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int S;
    if (!(cin >> S)) return 0;
    
    cout << fixed << setprecision(4);
    
    while (S--) {
        int N, i;
        double p;
        cin >> N >> p >> i;
        
        if (p < 1e-9) {
            cout << 0.0000 << "\n";
        } else if (p > 1.0 - 1e-9) {
            if (i == 1) {
                cout << 1.0000 << "\n";
            } else {
                cout << 0.0000 << "\n";
            }
        } else {
            double q = 1.0 - p;
            double qN = pow(q, N);
            double qi_1 = pow(q, i - 1);
            double prob = (qi_1 * p) / (1.0 - qN);
            cout << prob << "\n";
        }
    }
    
    return 0;
}
