#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Root {
    double a, b;
};

bool cmp(const Root& r1, const Root& r2) {
    if (r1.a < r2.a - EPS) return true;
    if (r2.a < r1.a - EPS) return false;
    if (r1.b < r2.b - EPS) return true;
    if (r2.b < r1.b - EPS) return false;
    return false;
}

double round_custom(double x) {
    double val = x * 1000.0;
    if (val > 0) val += EPS;
    if (val < 0) val -= EPS;
    long long rounded = (long long)round(val);
    if (rounded == 0) return 0.0;
    return (double)rounded / 1000.0;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<Root> roots;
        for (int k = 0; k < n; ++k) {
            double angle = 2.0 * PI * k / n;
            roots.push_back({cos(angle), sin(angle)});
        }
        sort(roots.begin(), roots.end(), cmp);
        for (size_t i = 0; i < roots.size(); ++i) {
            printf("%.3f %.3f\n", round_custom(roots[i].a), round_custom(roots[i].b));
        }
    }
    return 0;
}
