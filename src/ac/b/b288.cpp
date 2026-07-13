#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<double> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }
        
        double max_cross = 0.0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double dx1 = x[j] - x[i];
                double dy1 = y[j] - y[i];
                for (int k = j + 1; k < n; ++k) {
                    double dx2 = x[k] - x[i];
                    double dy2 = y[k] - y[i];
                    double cross = dx1 * dy2 - dy1 * dx2;
                    if (cross < 0) cross = -cross;
                    if (cross > max_cross) {
                        max_cross = cross;
                    }
                }
            }
        }
        
        cout << fixed << setprecision(6) << max_cross / 2.0 << "\n";
    }
    
    return 0;
}
