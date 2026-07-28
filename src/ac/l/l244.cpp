#include <cstdio>
#include <cmath>
#include <vector>

struct Point {
    double x, y;
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double point_to_segment(const Point& p, const Point& a, const Point& b) {
    double dx = b.x - a.x, dy = b.y - a.y;
    if (dx == 0.0 && dy == 0.0) return dist(p, a);
    double t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (dx * dx + dy * dy);
    if (t <= 0.0) return dist(p, a);
    if (t >= 1.0) return dist(p, b);
    Point proj = {a.x + t * dx, a.y + t * dy};
    return dist(p, proj);
}

int main() {
    double x, y;
    int n;
    while (std::scanf("%lf %lf %d", &x, &y, &n) == 3) {
        std::vector<Point> pts(n + 1);
        for (int i = 0; i <= n; ++i) {
            std::scanf("%lf %lf", &pts[i].x, &pts[i].y);
        }
        double ans = 1e18;
        for (int i = 0; i < n; ++i) {
            double d = point_to_segment({x, y}, pts[i], pts[i + 1]);
            if (d < ans) ans = d;
        }
        std::printf("%.16g\n", ans);
    }
    return 0;
}
