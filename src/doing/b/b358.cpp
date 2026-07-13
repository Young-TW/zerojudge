#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

struct Girl {
    int id;
    double area;
};

const double eps = 1e-9;

vector<Point> cut(const vector<Point>& poly, double a, double b, double c) {
    vector<Point> np;
    int n = poly.size();
    if (n == 0) return np;
    for (int i = 0; i < n; i++) {
        Point cur = poly[i];
        Point nxt = poly[(i + 1) % n];
        double val_cur = a * cur.x + b * cur.y + c;
        double val_nxt = a * nxt.x + b * nxt.y + c;
        if (val_cur < eps) {
            np.push_back(cur);
        }
        if ((val_cur > eps && val_nxt < -eps) || (val_cur < -eps && val_nxt > eps)) {
            double t = val_cur / (val_cur - val_nxt);
            Point inter;
            inter.x = cur.x + t * (nxt.x - cur.x);
            inter.y = cur.y + t * (nxt.y - cur.y);
            np.push_back(inter);
        }
    }
    return np;
}

double polygonArea(const vector<Point>& poly) {
    int n = poly.size();
    if (n < 3) return 0.0;
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (poly[i].x * poly[j].y - poly[j].x * poly[i].y);
    }
    return fabs(area) / 2.0;
}

bool cmp(const Girl& a, const Girl& b) {
    if (fabs(a.area - b.area) > 1e-8) return a.area > b.area;
    return a.id < b.id;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, A, B;
    int case_num = 1;
    while (cin >> N >> A >> B) {
        vector<Point> pts(N);
        for (int i = 0; i < N; i++) {
            cin >> pts[i].x >> pts[i].y;
        }
        
        vector<Girl> girls(N);
        for (int i = 0; i < N; i++) {
            vector<Point> poly;
            poly.push_back({0.0, 0.0});
            poly.push_back({(double)A, 0.0});
            poly.push_back({(double)A, (double)B});
            poly.push_back({0.0, (double)B});
            
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                double a = 2.0 * (pts[j].x - pts[i].x);
                double b = 2.0 * (pts[j].y - pts[i].y);
                double c = pts[i].x * pts[i].x - pts[j].x * pts[j].x + pts[i].y * pts[i].y - pts[j].y * pts[j].y;
                poly = cut(poly, a, b, c);
                if (poly.empty()) break;
            }
            girls[i].id = i + 1;
            girls[i].area = polygonArea(poly);
        }
        
        sort(girls.begin(), girls.end(), cmp);
        
        cout << "Case " << case_num << ":";
        for (int i = 0; i < N; i++) {
            cout << " " << girls[i].id;
        }
        cout << "\n";
        case_num++;
    }
    
    return 0;
}
