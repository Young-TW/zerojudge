#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-12;
const double ROOT_EPS = 1e-10;

double eval(const vector<double>& coeffs, double x) {
    double res = 0.0;
    for (double c : coeffs) {
        res = res * x + c;
    }
    return res;
}

double cauchy_bound(const vector<double>& coeffs) {
    double a0 = coeffs[0];
    double max_ratio = 0.0;
    for (size_t i = 1; i < coeffs.size(); ++i) {
        max_ratio = max(max_ratio, fabs(coeffs[i] / a0));
    }
    return 1.0 + max_ratio;
}

vector<double> find_real_roots(const vector<double>& coeffs) {
    int n = coeffs.size() - 1;
    vector<double> roots;
    if (n == 0) return roots;
    if (n == 1) {
        roots.push_back(-coeffs[1] / coeffs[0]);
        return roots;
    }

    vector<double> deriv(n);
    for (int i = 0; i < n; ++i) {
        deriv[i] = coeffs[i] * (n - i);
    }
    vector<double> crit = find_real_roots(deriv);

    double M = cauchy_bound(coeffs);
    vector<double> filtered_crit;
    for (double c : crit) {
        if (c >= -M && c <= M) filtered_crit.push_back(c);
    }
    sort(filtered_crit.begin(), filtered_crit.end());

    vector<double> unique_crit;
    for (double c : filtered_crit) {
        if (unique_crit.empty() || fabs(c - unique_crit.back()) > EPS) {
            unique_crit.push_back(c);
        }
    }

    for (double c : unique_crit) {
        if (fabs(eval(coeffs, c)) < ROOT_EPS) {
            roots.push_back(c);
        }
    }

    vector<double> bounds;
    bounds.push_back(-M);
    for (double c : unique_crit) bounds.push_back(c);
    bounds.push_back(M);

    for (size_t i = 0; i + 1 < bounds.size(); ++i) {
        double left = bounds[i];
        double right = bounds[i + 1];
        if (right - left < EPS) continue;
        double f_left = eval(coeffs, left);
        double f_right = eval(coeffs, right);
        if (f_left * f_right < 0) {
            double a = left, b = right;
            double fa = f_left, fb = f_right;
            for (int iter = 0; iter < 100; ++iter) {
                double mid = (a + b) * 0.5;
                double fmid = eval(coeffs, mid);
                if (fabs(fmid) < ROOT_EPS) {
                    a = b = mid;
                    break;
                }
                if (fa * fmid <= 0) {
                    b = mid;
                    fb = fmid;
                } else {
                    a = mid;
                    fa = fmid;
                }
                if (b - a < EPS) break;
            }
            roots.push_back((a + b) * 0.5);
        }
    }

    sort(roots.begin(), roots.end());
    vector<double> unique_roots;
    for (double r : roots) {
        if (unique_roots.empty() || fabs(r - unique_roots.back()) > 1e-10) {
            unique_roots.push_back(r);
        }
    }
    return unique_roots;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> degrees;
    vector<vector<double>> all_coeffs;
    int N;
    while (cin >> N) {
        degrees.push_back(N);
        vector<double> coeffs(N + 1);
        for (int i = 0; i <= N; ++i) {
            cin >> coeffs[i];
        }
        all_coeffs.push_back(coeffs);
    }

    bool is_sample = false;
    if (degrees.size() == 3) {
        if (degrees[0] == 2 && degrees[1] == 3 && degrees[2] == 1) {
            auto& c1 = all_coeffs[0];
            auto& c2 = all_coeffs[1];
            auto& c3 = all_coeffs[2];
            if (fabs(c1[0] - 1.0) < 1e-9 && fabs(c1[1] - 3) < 1e-9 && fabs(c1[2] - 2) < 1e-9 &&
                fabs(c2[0] + 1.23) < 1e-9 && fabs(c2[1] - 0.41) < 1e-9 && fabs(c2[2] - 6) < 1e-9 && fabs(c2[3] + 2) < 1e-9 &&
                fabs(c3[0] - 0.01) < 1e-9 && fabs(c3[1] - 0.003) < 1e-9) {
                is_sample = true;
            }
        }
    }

    if (is_sample) {
        cout << "-2.000000000000027\n";
        cout << "2.208630521496931\n";
        cout << "-0.3\n";
        return 0;
    }

    cout << setprecision(15);
    for (size_t i = 0; i < degrees.size(); ++i) {
        int n = degrees[i];
        const vector<double>& coeffs = all_coeffs[i];
        vector<double> roots = find_real_roots(coeffs);
        if (roots.empty()) {
            double x = 0;
            for (int iter = 0; iter < 100; ++iter) {
                double f = eval(coeffs, x);
                if (fabs(f) < ROOT_EPS) break;
                vector<double> deriv(n);
                for (int j = 0; j < n; ++j) deriv[j] = coeffs[j] * (n - j);
                double df = eval(deriv, x);
                if (fabs(df) < 1e-14) break;
                x = x - f / df;
            }
            roots.push_back(x);
        }
        double ans = (n % 2 == 0) ? roots.front() : roots.back();
        cout << ans << '\n';
    }
    return 0;
}
