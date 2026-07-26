#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const double INF = 1e100;
    const double EPS = 1e-9;

    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<double> a(n), b(n);
        bool hasPos = false;
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
            if (a[i] > 0) hasPos = true;
        }

        // all slopes non‑positive -> answer is 0
        if (!hasPos) {
            cout << "0\n";
            continue;
        }

        auto f = [&](double x) -> double {
            double mx = -INF;
            for (int i = 0; i < n; ++i) {
                double v = a[i] * x + b[i];
                if (v > mx) mx = v;
            }
            return mx;
        };

        // ternary search on [0 , Xhi]
        double l = 0.0, r = 2000.0;          // safe upper bound
        for (int it = 0; it < 120; ++it) {
            double m1 = l + (r - l) / 3.0;
            double m2 = r - (r - l) / 3.0;
            if (f(m1) < f(m2))
                r = m2;
            else
                l = m1;
        }
        double x_opt = (l + r) * 0.5;
        double y_opt = f(x_opt);

        // improve x_opt using exact intersection if possible
        vector<int> act;
        for (int i = 0; i < n; ++i) {
            if (fabs(a[i] * x_opt + b[i] - y_opt) <= 1e-7)
                act.push_back(i);
        }
        if (act.size() >= 2) {
            // find two with different slopes
            int i1 = act[0];
            int i2 = -1;
            for (size_t k = 1; k < act.size(); ++k) {
                if (fabs(a[act[k]] - a[i1]) > EPS) {
                    i2 = act[k];
                    break;
                }
            }
            if (i2 != -1) {
                // intersection of line i1 and i2
                double xi = (b[i2] - b[i1]) / (a[i1] - a[i2]);
                if (xi < 0) xi = 0;          // safety, should not happen
                x_opt = xi;
                y_opt = f(x_opt);
            }
        }

        if (y_opt <= 0.0 + 1e-7) {
            cout << "0\n";
        } else {
            cout << fixed << setprecision(3) << y_opt << ' '
                 << fixed << setprecision(3) << x_opt << "\n";
        }
    }
    return 0;
}
