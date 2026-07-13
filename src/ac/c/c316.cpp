#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

long long dist2(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        if (N < 2) {
            if (N == 1) {
                int x, y;
                cin >> x >> y;
            }
            continue;
        }
        
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) {
            cin >> pts[i].x >> pts[i].y;
        }
        
        long long max_d = -1;
        int best_i = -1, best_j = -1;
        
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                long long d = dist2(pts[i], pts[j]);
                if (d > max_d) {
                    max_d = d;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        
        cout << best_i << " " << best_j << "\n";
    }
    return 0;
}
