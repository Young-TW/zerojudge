#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return x < other.x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int C;
    while (cin >> C) {
        while (C--) {
            int N;
            cin >> N;
            vector<Point> points(N);
            for (int i = 0; i < N; ++i) {
                cin >> points[i].x >> points[i].y;
            }
            sort(points.begin(), points.end());
            
            double total_length = 0.0;
            int max_y = 0;
            for (int i = N - 2; i >= 0; --i) {
                if (points[i].y > max_y) {
                    double dx = points[i+1].x - points[i].x;
                    double dy = points[i+1].y - points[i].y;
                    double len = sqrt(dx * dx + dy * dy);
                    double ratio = (double)(points[i].y - max_y) / (points[i].y - points[i+1].y);
                    total_length += len * ratio;
                    max_y = points[i].y;
                }
            }
            cout << fixed << setprecision(2) << total_length << "\n";
        }
    }
    return 0;
}
