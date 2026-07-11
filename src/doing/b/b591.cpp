#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        vector<double> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
        }

        double min_y = numeric_limits<double>::max();
        double best_x = 0.0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (a[i] == a[j]) continue;
                double x = (b[j] - b[i]) / (a[i] - a[j]);
                if (x < 0) x = 0;
                double y = a[i] * x + b[i];
                bool valid = true;
                for (int k = 0; k < n; ++k) {
                    if (y < a[k] * x + b[k] - 1e-9) {
                        valid = false;
                        break;
                    }
                }
                if (valid && y < min_y) {
                    min_y = y;
                    best_x = x;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            double x = 0.0;
            double y = a[i] * x + b[i];
            bool valid = true;
            for (int k = 0; k < n; ++k) {
                if (y < a[k] * x + b[k] - 1e-9) {
                    valid = false;
                    break;
                }
            }
            if (valid && y < min_y) {
                min_y = y;
                best_x = x;
            }
        }

        if (min_y <= 0) {
            cout << "0\n";
        } else {
            cout << fixed << setprecision(3) << min_y << " " << best_x << "\n";
        }
    }

    return 0;
}
