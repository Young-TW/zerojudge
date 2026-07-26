#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
    Point() {}
    Point(long double _x, long double _y) : x(_x), y(_y) {}
    Point operator + (const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator * (long double k) const { return Point(x * k, y * k); }
};

static const long double EPS = 1e-12L;          // for geometric tests
static const long double EPS_PROB = 1e-6L;      // for final comparison

/* clip convex polygon with half‑plane  n·X ≤ c  */
vector<Point> clipHalfPlane(const vector<Point>& poly,
                            const Point& n, long double c)
{
    vector<Point> res;
    int m = (int)poly.size();
    if (m == 0) return res;
    for (int i = 0; i < m; ++i) {
        const Point& cur = poly[i];
        const Point& nxt = poly[(i + 1) % m];
        long double valCur = n.x * cur.x + n.y * cur.y - c;
        long double valNxt = n.x * nxt.x + n.y * nxt.y - c;
        bool inCur = (valCur <= EPS);
        bool inNxt = (valNxt <= EPS);
        if (inCur) res.push_back(cur);
        if (inCur ^ inNxt) {                     // edge crosses the line
            long double t = valCur / (valCur - valNxt); // 0..1
            Point inter = cur + (nxt - cur) * t;
            res.push_back(inter);
        }
    }
    return res;
}

/* polygon area – absolute value */
long double polygonArea(const vector<Point>& poly)
{
    int n = (int)poly.size();
    if (n < 3) return 0.0L;
    long double s = 0.0L;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        s += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabsl(s) * 0.5L;
}

struct Girl {
    int id;                 // 1‑based
    long double prob;      // area / totalArea
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, A, B;
    int caseNo = 1;
    while (cin >> N >> A >> B) {
        vector<Point> p(N);
        for (int i = 0; i < N; ++i) {
            long double x, y;
            cin >> x >> y;
            p[i] = Point(x, y);
        }

        long double totalArea = (long double)A * (long double)B;
        vector<Girl> girls(N);

        // rectangle polygon (counter‑clockwise)
        vector<Point> rect = {
            Point(0.0L, 0.0L),
            Point((long double)A, 0.0L),
            Point((long double)A, (long double)B),
            Point(0.0L, (long double)B)
        };

        for (int i = 0; i < N; ++i) {
            vector<Point> poly = rect;
            for (int j = 0; j < N; ++j) if (i != j) {
                // normal = Pj - Pi
                Point n = p[j] - p[i];
                // c = (|Pj|² - |Pi|²) / 2
                long double c = (p[j].x * p[j].x + p[j].y * p[j].y
                                - p[i].x * p[i].x - p[i].y * p[i].y) * 0.5L;
                poly = clipHalfPlane(poly, n, c);
                if (poly.empty()) break;
            }
            long double a = polygonArea(poly);
            girls[i].id = i + 1;
            girls[i].prob = a / totalArea;
        }

        sort(girls.begin(), girls.end(),
            [](const Girl& a, const Girl& b) {
                long double diff = a.prob - b.prob;
                if (fabsl(diff) > EPS_PROB) return diff > 0;
                return a.id < b.id;
            });

        cout << "Case " << caseNo << ":";
        for (const auto& g : girls) cout << ' ' << g.id;
        cout << '\n';
        ++caseNo;
    }
    return 0;
}
