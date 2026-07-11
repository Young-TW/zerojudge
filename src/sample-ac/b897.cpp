#include <iostream>
#include <cmath>

using namespace std;

const long double PI = acosl(-1.0L);
const long double E = expl(1.0L);
const long double LN10 = logl(10.0L);

long double log_fact(long long n) {
    if (n <= 1) return 0.0L;
    if (n < 10000) {
        long double res = 0.0L;
        for (int i = 2; i <= n; ++i) {
            res += log10l((long double)i);
        }
        return res;
    }
    long double nd = (long double)n;
    long double res = nd * log10l(nd) - nd * log10l(E) + 0.5L * log10l(2.0L * PI * nd);
    res += 1.0L / (12.0L * nd * LN10);
    res -= 1.0L / (360.0L * nd * nd * nd * LN10);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n, k;
    while (cin >> n >> k) {
        if (k > n - k) {
            k = n - k;
        }
        long double logC = 0.0L;
        if (k < 10000) {
            for (long long i = 0; i < k; ++i) {
                logC += log10l((long double)(n - i));
                logC -= log10l((long double)(i + 1));
            }
        } else {
            logC = log_fact(n) - log_fact(k) - log_fact(n - k);
        }
        long long ans = (long long)floorl(logC + 1e-9L) + 1;
        cout << ans << "\n";
    }
    return 0;
}
