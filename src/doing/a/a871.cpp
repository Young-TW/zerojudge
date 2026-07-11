#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(2);
    
    int n;
    while (cin >> n) {
        vector<double> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }
        
        double area = 0.0;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += (x[i] * y[j] - x[j] * y[i]);
        }
        
        area = fabs(area) / 2.0;
        cout << area + 1e-9 << "\n";
    }
    
    return 0;
}
