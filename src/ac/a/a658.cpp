#include <bits/stdc++.h>
using namespace std;

static const int ITER_ROOT = 60;   // iterations for solving one segment
static const int ITER_MU   = 80;   // iterations for the outer binary search

// solve 2*mu*k*(v - w) = 1/v^2  ,  v > 0
static double solve_speed(double mu, double k, double w)
{
    auto f = [&](double v) -> double {
        return 2.0 * mu * k * (v - w) - 1.0 / (v * v);
    };

    double lo = max(0.0, w);          // speed cannot be negative
    double hi = lo + 1.0;
    while (f(hi) < 0.0) hi *= 2.0;    // enlarge interval until root is inside

    for (int it = 0; it < ITER_ROOT; ++it) {
        double mid = (lo + hi) * 0.5;
        if (f(mid) < 0.0) lo = mid;
        else              hi = mid;
    }
    return (lo + hi) * 0.5;
}

// total energy for a given mu
static double total_energy(double mu,
                           const vector<double>& s,
                           const vector<double>& k,
                           const vector<double>& w)
{
    double e = 0.0;
    int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        double v = solve_speed(mu, k[i], w[i]);
        double diff = v - w[i];
        e += k[i] * diff * diff * s[i];
    }
    return e;
}

// total time for a given mu
static double total_time(double mu,
                         const vector<double>& s,
                         const vector<double>& k,
                         const vector<double>& w)
{
    double t = 0.0;
    int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        double v = solve_speed(mu, k[i], w[i]);
        t += s[i] / v;
    }
    return t;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    double EU;
    while (cin >> N >> EU) {
        vector<double> s(N), k(N), w(N);
        for (int i = 0; i < N; ++i) cin >> s[i] >> k[i] >> w[i];

        // ----- find mu -------------------------------------------------
        double lo = 0.0, hi = 1.0;
        while (total_energy(hi, s, k, w) > EU) hi *= 2.0;

        for (int it = 0; it < ITER_MU; ++it) {
            double mid = (lo + hi) * 0.5;
            if (total_energy(mid, s, k, w) > EU) lo = mid;
            else                                   hi = mid;
        }
        double mu = (lo + hi) * 0.5;

        // ----- compute minimal time ------------------------------------
        double ans = total_time(mu, s, k, w);
        cout << fixed << setprecision(8) << ans << "\n";
    }
    return 0;
}
