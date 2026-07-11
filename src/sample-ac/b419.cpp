#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-10;

double log_factorial(int n) {
    if (n <= 1) return 0.0;
    return log(sqrt(2 * PI * n)) + n * log(n / exp(1.0)) + 1.0 / (12 * n) - 1.0 / (360 * n * n * n);
}

double log_combination(int n, int k) {
    if (k < 0 || k > n) return -1e18;
    return log_factorial(n) - log_factorial(k) - log_factorial(n - k);
}

double normal_cdf(double x) {
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

double binomial_probability(int n, int k, double p) {
    if (k < 0 || k > n) return 0.0;
    return exp(log_combination(n, k) + k * log(p) + (n - k) * log(1 - p));
}

double binomial_cdf(int n, int k, double p) {
    if (k < 0) return 0.0;
    if (k >= n) return 1.0;
    double mu = n * p;
    double sigma = sqrt(n * p * (1 - p));
    double z = (k - mu) / sigma;
    return normal_cdf(z);
}

double solve(int n, int a, int b) {
    if (n == 0) return 1.0;
    if (a > b) return 0.0;
    double p = 0.5;
    if (n <= 1000000) {
        double total = 0.0;
        for (int k = a; k <= b; ++k) {
            total += binomial_probability(n, k, p);
        }
        return total;
    } else {
        double cdf_b = binomial_cdf(n, b, p);
        double cdf_a_minus_1 = binomial_cdf(n, a - 1, p);
        return cdf_b - cdf_a_minus_1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(4);
    int n, a, b;
    while (cin >> n >> a >> b) {
        double result = solve(n, a, b);
        cout << result << '\n';
    }
    return 0;
}
