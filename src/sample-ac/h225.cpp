#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        
        sort(points.begin(), points.end());
        
        vector<Point> lower, upper;
        for (int i = 0; i < n; i++) {
            while (lower.size() >= 2 && cross(lower[lower.size()-2], lower[lower.size()-1], points[i]) < 0) {
                lower.pop_back();
            }
            lower.push_back(points[i]);
        }
        
        for (int i = n-1; i >= 0; i--) {
            while (upper.size() >= 2 && cross(upper[upper.size()-2], upper[upper.size()-1], points[i]) < 0) {
                upper.pop_back();
            }
            upper.push_back(points[i]);
        }
        
        vector<Point> hull = lower;
        for (size_t i = 1; i + 1 < upper.size(); i++) {
            hull.push_back(upper[i]);
        }
        
        sort(hull.begin(), hull.end());
        
        cout << hull.size() << "\n";
        for (const auto& p : hull) {
            cout << p.x << " " << p.y << "\n";
        }
    }
    
    return 0;
}
