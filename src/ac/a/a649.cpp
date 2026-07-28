#include <bits/stdc++.h>
using namespace std;

struct Segment {
    double z0, z1;      // height interval
    double r0, r1;      // radius at ends
    double A, B;        // r(z) = A*z + B
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    double alpha;
    while (cin >> n >> alpha) {
        vector<double> h(n + 1);
        for (int i = 0; i <= n; ++i) cin >> h[i];
        vector<double> r(n + 1);          // r[1..n], r[0] unused
        for (int i = 1; i <= n; ++i) cin >> r[i];

        double s = 1.0 / tan(alpha);      // cot(alpha)

        // build segments
        vector<Segment> seg;
        double curZ = h[0];
        for (int i = 1; i <= n; ++i) {
            double nextZ = curZ + h[i];
            double rStart = r[i];
            double rEnd = (i == n) ? 0.0 : r[i + 1];
            Segment sg;
            sg.z0 = curZ; sg.z1 = nextZ;
            sg.r0 = rStart; sg.r1 = rEnd;
            if (abs(sg.z1 - sg.z0) < 1e-12) {
                sg.A = 0.0; sg.B = sg.r0;
            } else {
                sg.A = (sg.r1 - sg.r0) / (sg.z1 - sg.z0);
                sg.B = sg.r0 - sg.A * sg.z0;
            }
            seg.push_back(sg);
            curZ = nextZ;
        }

        // compute x range
        double xMin = 1e100, xMax = -1e100;
        for (auto &sg : seg) {
            // evaluate at both ends
            for (int k = 0; k < 2; ++k) {
                double z = (k == 0) ? sg.z0 : sg.z1;
                double rad = sg.A * z + sg.B;
                double left  = -s * z - rad;
                double right = -s * z + rad;
                xMin = min(xMin, left);
                xMax = max(xMax, right);
            }
        }

        // function giving 2*y_max(x)
        auto f = [&](double x) -> double {
            double best = 0.0;
            for (const auto &sg : seg) {
                // quadratic coefficients for h(z) = r(z)^2 - (x + s*z)^2
                double A = sg.A;
                double B = sg.B;
                double a = A * A - s * s;
                double b = 2.0 * (A * B - x * s);
                double c = B * B - x * x;

                // evaluate at endpoints
                auto eval = [&](double z) -> double {
                    return a * z * z + b * z + c;
                };
                double v0 = eval(sg.z0);
                double v1 = eval(sg.z1);
                double localMax = max(v0, v1);

                // possible interior maximum
                if (fabs(a) > 1e-12) {
                    double zv = -b / (2.0 * a);
                    if (zv > sg.z0 && zv < sg.z1) {
                        double vv = eval(zv);
                        localMax = max(localMax, vv);
                    }
                }
                best = max(best, localMax);
            }
            if (best <= 0.0) return 0.0;
            return 2.0 * sqrt(best);
        };

        // adaptive Simpson
        function<double(double,double,double,double)> simpson = [&](double fl,double fm,double fr,double h)->double{
            return (fl + 4*fm + fr) * h / 6.0;
        };
        function<double(double,double,double,double,double,double,int)> asr;
        asr = [&](double a,double b,double fa,double fm,double fb,double whole,int depth)->double{
            double m = (a + b) * 0.5;
            double lm = (a + m) * 0.5;
            double rm = (m + b) * 0.5;
            double flm = f(lm);
            double frm = f(rm);
            double left = simpson(fa, flm, fm, (m - a));
            double right = simpson(fm, frm, fb, (b - m));
            double diff = left + right - whole;
            if (depth <= 0 || fabs(diff) < 1e-7) return left + right + diff / 15.0;
            return asr(a, m, fa, flm, fm, left, depth-1) +
                   asr(m, b, fm, frm, fb, right, depth-1);
        };

        double fa = f(xMin);
        double fb = f(xMax);
        double fm = f((xMin + xMax) * 0.5);
        double whole = simpson(fa, fm, fb, (xMax - xMin));
        double area = asr(xMin, xMax, fa, fm, fb, whole, 20);

        cout.setf(ios::fixed);
        cout << setprecision(2) << area + 1e-9 << "\n";
    }
    return 0;
}
