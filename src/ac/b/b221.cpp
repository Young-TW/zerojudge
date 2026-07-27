#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
};

static double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}
static double cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

/* ---------- convex hull, monotone chain, CCW order ---------- */
static vector<Point> convex_hull(vector<Point>& pts) {
    sort(pts.begin(), pts.end(),
         [](const Point& a, const Point& b) {
             if (a.x != b.x) return a.x < b.x;
             return a.y < b.y;
         });
    int n = (int)pts.size();
    vector<Point> lower, upper;
    for (int i = 0; i < n; ++i) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size() - 2], lower.back(), pts[i]) <= 0)
            lower.pop_back();
        lower.push_back(pts[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
        while (upper.size() >= 2 &&
               cross(upper[upper.size() - 2], upper.back(), pts[i]) <= 0)
            upper.pop_back();
        upper.push_back(pts[i]);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;               // CCW, no duplicate first point
}

/* ---------- polygon area (absolute) ---------- */
static double polygon_area(const vector<Point>& poly) {
    int m = (int)poly.size();
    if (m < 3) return 0.0;
    double s = 0.0;
    for (int i = 0; i < m; ++i) {
        const Point& p = poly[i];
        const Point& q = poly[(i + 1) % m];
        s += cross(p, q);
    }
    return fabs(s) * 0.5;
}

/* ---------- clip convex polygon with half‑plane y - a*x >= 0 ---------- */
static vector<Point> clip_halfplane(const vector<Point>& poly, double a) {
    vector<Point> res;
    int m = (int)poly.size();
    if (m == 0) return res;
    auto f = [&](const Point& p) { return p.y - a * p.x; };
    for (int i = 0; i < m; ++i) {
        const Point& cur = poly[i];
        const Point& nxt = poly[(i + 1) % m];
        double fc = f(cur);
        double fn = f(nxt);
        bool inc = fc >= 0;
        bool inn = fn >= 0;
        if (inc) res.push_back(cur);
        if (inc != inn) {
            double t = fc / (fc - fn);          // 0 .. 1
            Point inter = cur + (nxt - cur) * t;
            res.push_back(inter);
        }
    }
    return res;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;

        vector<Point> hull = convex_hull(pts);
        double total = polygon_area(hull);
        if (total == 0.0) {               // degenerate, should not happen
            cout << "0.0000\n";
            continue;
        }

        double minSlope = 1e100, maxSlope = -1e100;
        for (const Point& p : hull) {
            double s = p.y / p.x;          // x > 0 guaranteed
            if (s < minSlope) minSlope = s;
            if (s > maxSlope) maxSlope = s;
        }

        double lo = minSlope, hi = maxSlope;
        const double half = total * 0.5;
        for (int it = 0; it < 70; ++it) { // enough for required precision
            double mid = (lo + hi) * 0.5;
            vector<Point> part = clip_halfplane(hull, mid);
            double a_mid = polygon_area(part);
            if (a_mid > half)   // too much area above → need larger slope
                lo = mid;
            else
                hi = mid;
        }
        double ans = (lo + hi) * 0.5;
        cout << fixed << setprecision(4) << ans << "\n";
    }
    return 0;
}
