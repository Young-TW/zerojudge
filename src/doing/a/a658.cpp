#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int N;
double EU;
vector<double> s, k, vp;

double solveV(double mu, int i) {
    double lo = max(1e-12, vp[i]);
    double hi = lo + 1.0;
    double kk = k[i], vpp = vp[i];
    auto f = [&](double v) { return 2.0*mu*kk*(v-vpp)*v*v - 1.0; };
    while (f(hi) < 0) hi *= 2.0;
    for (int it = 0; it < 200; it++) {
        double mid = (lo + hi) * 0.5;
        if (f(mid) < 0) lo = mid; else hi = mid;
    }
    return (lo+hi)*0.5;
}

int main() {
    while (scanf("%d %lf", &N, &EU) == 2) {
        s.assign(N, 0); k.assign(N, 0); vp.assign(N, 0);
        for (int i = 0; i < N; i++) {
            scanf("%lf %lf %lf", &s[i], &k[i], &vp[i]);
        }
        double lo = 0, hi = 1e18;
        auto energy = [&](double mu) {
            double e = 0;
            for (int i = 0; i < N; i++) {
                double v = solveV(mu, i);
                e += k[i]*(v - vp[i])*(v - vp[i]) * s[i];
            }
            return e;
        };
        for (int it = 0; it < 100; it++) {
            double mid = (lo + hi) * 0.5;
            if (energy(mid) > EU) lo = mid; else hi = mid;
        }
        double mu = (lo+hi)*0.5;
        double T = 0;
        for (int i = 0; i < N; i++) {
            double v = solveV(mu, i);
            T += s[i] / v;
        }
        printf("%.8f\n", T);
    }
    return 0;
}
