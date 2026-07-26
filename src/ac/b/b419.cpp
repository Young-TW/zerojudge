#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

static const long double LOG2 = logl(2.0L);
static const long double SQRT2 = sqrtl(2.0L);

/* normal CDF using long double */
static inline long double normal_cdf(long double z) {
    return 0.5L * (1.0L + erfl(z / SQRT2));
}

/* exact probability for small n (n <= LIMIT) */
static long double exact_binom_prob(int n, int a, int b) {
    long double sum = 0.0L;
    long double logDen = n * LOG2;               // log(2^n)
    for (int k = a; k <= b; ++k) {
        long double logp = lgammal(n + 1.0L) - lgammal(k + 1.0L) - lgammal(n - k + 1.0L);
        logp -= logDen;
        sum += expl(logp);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(4);

    const int LIMIT = 5000;          // threshold for exact computation
    long long n;
    int a, b;
    while (cin >> n >> a >> b) {
        long double ans = 0.0L;

        if (a == 0 && b == (int)n) {          // whole range
            ans = 1.0L;
        }
        else if (n <= LIMIT) {
            ans = exact_binom_prob((int)n, a, b);
        } else {
            // upper bound
            long double upper;
            if (b == (int)n) {
                upper = 1.0L;
            } else {
                long double z1 = ((long double)(2LL * b + 1) - (long double)n) / sqrtl((long double)n);
                upper = normal_cdf(z1);
            }

            // lower bound (a-1)
            long double lower;
            if (a == 0) {
                lower = 0.0L;
            } else {
                long double z0 = ((long double)(2LL * a - 1) - (long double)n) / sqrtl((long double)n);
                lower = normal_cdf(z0);
            }

            ans = upper - lower;
            if (ans < 0.0L) ans = 0.0L;
            if (ans > 1.0L) ans = 1.0L;
        }

        cout << (double)ans << '\n';
    }
    return 0;
}
