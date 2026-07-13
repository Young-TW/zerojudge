#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

long long cross(Point a, Point b, Point c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

bool on_segment(Point a, Point b, Point c) {
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

bool intersect(Point p1, Point p2, Point p3, Point p4) {
    long long d1 = cross(p3, p4, p1);
    long long d2 = cross(p3, p4, p2);
    long long d3 = cross(p1, p2, p3);
    long long d4 = cross(p1, p2, p4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return true;
    }
    
    if (d1 == 0 && on_segment(p3, p4, p1)) return true;
    if (d2 == 0 && on_segment(p3, p4, p2)) return true;
    if (d3 == 0 && on_segment(p1, p2, p3)) return true;
    if (d4 == 0 && on_segment(p1, p2, p4)) return true;

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        for (int t = 0; t < T; ++t) {
            if (t > 0) cout << "\n";
            
            int n;
            cin >> n;
            vector<Point> p1(n), p2(n);
            for (int i = 0; i < n; ++i) {
                cin >> p1[i].x >> p1[i].y >> p2[i].x >> p2[i].y;
            }
            
            vector<vector<bool>> connected(n, vector<bool>(n, false));
            for (int i = 0; i < n; ++i) {
                connected[i][i] = true;
                for (int j = i + 1; j < n; ++j) {
                    if (intersect(p1[i], p2[i], p1[j], p2[j])) {
                        connected[i][j] = true;
                        connected[j][i] = true;
                    }
                }
            }
            
            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < n; ++i) {
                    if (connected[i][k]) {
                        for (int j = 0; j < n; ++j) {
                            if (connected[k][j]) {
                                connected[i][j] = true;
                            }
                        }
                    }
                }
            }
            
            int a, b;
            while (cin >> a >> b) {
                if (a == 0 && b == 0) break;
                if (connected[a - 1][b - 1]) {
                    cout << "CONNECTED\n";
                } else {
                    cout << "NOT CONNECTED\n";
                }
            }
        }
    }
    
    return 0;
}
