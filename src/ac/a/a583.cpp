#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    double x, y;
};

static double dist2(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

static Point pts[25];

static double closest(int l, int r) {
    if (r - l + 1 <= 3) {
        double best = 1e18;
        for (int i = l; i <= r; i++)
            for (int j = i + 1; j <= r; j++)
                best = min(best, dist2(pts[i], pts[j]));
        return best;
    }
    int mid = (l + r) / 2;
    double midx = pts[mid].x;
    double dl = closest(l, mid);
    double dr = closest(mid + 1, r);
    double d = min(dl, dr);
    vector<Point> strip;
    for (int i = l; i <= r; i++)
        if ((pts[i].x - midx) * (pts[i].x - midx) < d)
            strip.push_back(pts[i]);
    sort(strip.begin(), strip.end(),
         [](const Point &a, const Point &b) { return a.y < b.y; });
    double ds = d;
    int sz = (int)strip.size();
    for (int i = 0; i < sz; i++)
        for (int j = i + 1; j < sz; j++) {
            double t = strip[j].y - strip[i].y;
            if (t * t >= ds) break;
            ds = min(ds, dist2(strip[i], strip[j]));
        }
    return min(d, ds);
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 0; i < m; i++)
            scanf("%lf %lf", &pts[i].x, &pts[i].y);
        sort(pts, pts + m,
             [](const Point &a, const Point &b) { return a.x < b.x; });
        double d2 = closest(0, m - 1);
        printf("%.4f\n", sqrt(d2));
    }
    return 0;
}
