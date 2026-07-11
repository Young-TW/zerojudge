#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

string format_complex(complex<double> z) {
    double re = z.real();
    double im = z.imag();
    auto round2 = [](double x) -> double {
        double r = round(x * 100.0) / 100.0;
        if (fabs(r) < 0.005) r = 0.0;
        return r;
    };
    re = round2(re);
    im = round2(im);
    char buf[50];
    if (im >= 0) {
        snprintf(buf, sizeof(buf), "%.2f+%.2fi", re, im);
    } else {
        snprintf(buf, sizeof(buf), "%.2f%.2fi", re, im);
    }
    return string(buf);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double ar, ai, br, bi, cr, ci;
    while (cin >> ar >> ai) {
        cin >> br >> bi;
        cin >> cr >> ci;
        complex<double> A(ar, ai), B(br, bi), C(cr, ci);
        complex<double> D = B * B - 4.0 * A * C;
        const double eps = 1e-9;
        if (abs(D) < eps) {
            complex<double> x = -B / (2.0 * A);
            cout << "the only x = " << format_complex(x) << '\n';
        } else {
            complex<double> sqrt_D = sqrt(D);
            complex<double> x1 = (-B + sqrt_D) / (2.0 * A);
            complex<double> x2 = (-B - sqrt_D) / (2.0 * A);
            vector<complex<double>> roots = {x1, x2};
            sort(roots.begin(), roots.end(), [](const complex<double>& a, const complex<double>& b) {
                if (a.real() < b.real()) return true;
                if (a.real() > b.real()) return false;
                return a.imag() < b.imag();
            });
            cout << "first x = " << format_complex(roots[0]) << ", second x = " << format_complex(roots[1]) << '\n';
        }
    }
    return 0;
}
