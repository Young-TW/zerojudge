#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        sort(points.begin(), points.end());

        vector<int> dp(n, 1);
        int max_count = 1;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (points[j].x < points[i].x && points[j].y < points[i].y) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_count = max(max_count, dp[i]);
        }

        cout << max_count << '\n';
    }

    return 0;
}
