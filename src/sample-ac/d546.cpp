#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
    bool operator < (const Point& p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator == (const Point& p) const {
        return x == p.x && y == p.y;
    }
    Point operator - (const Point& p) const {
        return {x - p.x, y - p.y};
    }
};

long long cross(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

vector<Point> convex_hull(vector<Point> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    int n = pts.size();
    if (n <= 2) return pts;
    vector<Point> hull(2 * n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m >= 2 && cross(hull[m-2], hull[m-1], pts[i]) <= 0) m--;
        hull[m++] = pts[i];
    }
    for (int i = n - 2, t = m + 1; i >= 0; i--) {
        while (m >= t && cross(hull[m-2], hull[m-1], pts[i]) <= 0) m--;
        hull[m++] = pts[i];
    }
    hull.resize(m - 1);
    return hull;
}

long long polygon_area2(const vector<Point>& pts) {
    long long area2 = 0;
    int n = pts.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area2 += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
    }
    if (area2 < 0) area2 = -area2;
    return area2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, a;
    while (cin >> n >> a) {
        vector<Point> pts(n);
        for (int i = 0; i < n; i++) {
            cin >> pts[i].x >> pts[i].y;
        }
        
        long long area_poly2 = polygon_area2(pts);
        vector<Point> hull = convex_hull(pts);
        long long area_conv2 = polygon_area2(hull);
        
        long long remove_area2 = area_conv2 - area_poly2;
        if (remove_area2 < 0) remove_area2 = 0;
        
        if (a <= 0) {
            cout << 0 << "\n";
        } else {
            long long denom = 2 * a;
            long long ans = (remove_area2 + denom - 1) / denom;
            cout << ans << "\n";
        }
    }
    return 0;
}
