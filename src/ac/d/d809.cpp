#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<long long> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }
        
        long long max_area2 = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    long long area2 = x[i] * y[j] + x[j] * y[k] + x[k] * y[i] -
                                     x[j] * y[i] - x[k] * y[j] - x[i] * y[k];
                    if (area2 < 0) area2 = -area2;
                    if (area2 > max_area2) {
                        max_area2 = area2;
                    }
                }
            }
        }
        
        double ans = max_area2 / 2.0;
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
