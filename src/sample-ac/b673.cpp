#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << fixed << setprecision(3);
    
    int m;
    while (cin >> m && m) {
        vector<double> r(m);
        for (int i = 0; i < m; ++i) {
            cin >> r[i];
        }
        
        sort(r.begin(), r.end());
        
        double min_width = 1e18;
        vector<double> x(m);
        
        do {
            double width = 0.0;
            for (int i = 0; i < m; ++i) {
                x[i] = r[i];
                for (int j = 0; j < i; ++j) {
                    x[i] = max(x[i], x[j] + 2.0 * sqrt(r[i] * r[j]));
                }
                width = max(width, x[i] + r[i]);
            }
            min_width = min(min_width, width);
        } while (next_permutation(r.begin(), r.end()));
        
        cout << min_width << "\n";
    }
    
    return 0;
}
