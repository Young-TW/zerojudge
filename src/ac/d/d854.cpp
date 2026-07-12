#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        auto f = [&](double x) {
            return ((a * x + b) * x + c) * x + d;
        };
        
        vector<double> roots;
        
        for (int i = -10000; i <= 10000; ++i) {
            double x1 = i / 100.0;
            double x2 = (i + 1) / 100.0;
            
            if (f(x1) * f(x2) <= 0) {
                double L = x1, R = x2;
                for (int j = 0; j < 100; ++j) {
                    double mid = (L + R) / 2.0;
                    if (f(L) * f(mid) <= 0) {
                        R = mid;
                    } else {
                        L = mid;
                    }
                }
                double root = (L + R) / 2.0;
                if (roots.empty() || fabs(root - roots.back()) > 0.5) {
                    roots.push_back(root);
                }
            }
        }
        
        cout << fixed << setprecision(2);
        for (size_t i = 0; i < roots.size(); ++i) {
            if (i > 0) cout << " ";
            cout << roots[i];
        }
        cout << "\n";
    }
    
    return 0;
}
