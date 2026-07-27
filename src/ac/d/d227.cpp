#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const double PI = 3.1415926;          // required precision
    double a;
    while (std::cin >> a) {
        double x = a * PI / 180.0;        // convert degree to radian

        int n = 1;                        // current exponent (odd)
        double term = x;                  // first term x / 1!
        double sum = term;                // accumulated sum

        if (std::fabs(term) > 0.01) {
            while (true) {
                n += 2;                                   // next odd exponent
                term = -term * x * x / ((n - 1) * n);     // recurrence
                sum += term;
                if (std::fabs(term) <= 0.01) break;      // condition satisfied
            }
        }

        std::cout << "N = " << n << '\n';
        std::cout << std::fixed << std::setprecision(6) << sum << '\n';
    }
    return 0;
}
