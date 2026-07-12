#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, z;
};

long long cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.z - a.z) - (b.z - a.z) * (c.x - a.x);
}

long long dist2(Point a, Point b) {
    long long dx = b.x - a.x;
    long long dz = b.z - a.z;
    return dx * dx + dz * dz;
}

int get_triangle_type(Point a, Point b, Point c) {
    long long d1 = dist2(b, c);
    long long d2 = dist2(a, c);
    long long d3 = dist2(a, b);
    
    long long c2 = d1;
    long long a2 = d2;
    long long b2 = d3;
    
    if (d2 > c2) {
        c2 = d2;
        a2 = d1;
        b2 = d3;
    }
    if (d3 > c2) {
        c2 = d3;
        a2 = d1;
        b2 = d2;
    }
    
    __int128 sum = (__int128)a2 + b2;
    if (sum == c2) return 1; // 直角
    if (sum < c2) return 0;  // 鈍角
    return 2;                // 銳角
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<Point> pts(n);
            for (int i = 0; i < n; ++i) {
                cin >> pts[i].x >> pts[i].z;
            }
            
            long long min_area2 = -1;
            int best_type = -1;
            
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    for (int k = j + 1; k < n; ++k) {
                        long long area2 = cross_product(pts[i], pts[j], pts[k]);
                        if (area2 < 0) area2 = -area2;
                        if (area2 == 0) continue;
                        
                        int type = get_triangle_type(pts[i], pts[j], pts[k]);
                        
                        if (min_area2 == -1 || area2 < min_area2 || (area2 == min_area2 && type < best_type)) {
                            min_area2 = area2;
                            best_type = type;
                        }
                    }
                }
            }
            
            if (best_type == 0) {
                cout << "Block of Gold ";
            } else if (best_type == 1) {
                cout << "Block of Diamond ";
            } else {
                cout << "Block of Emerald ";
            }
            
            cout << min_area2 / 2;
            if (min_area2 % 2 != 0) {
                cout << ".5";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
