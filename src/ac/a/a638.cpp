#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <set>

using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point& other) const {
        return y < other.y;
    }
};

double closest_pair(vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return 0.0;

    int block_size = sqrt(n) + 1;
    vector<vector<Point>> blocks((n + block_size - 1) / block_size);

    for (int i = 0; i < n; ++i) {
        blocks[i / block_size].push_back(points[i]);
    }

    for (auto& block : blocks) {
        sort(block.begin(), block.end());
    }

    double min_dist = 1e18;
    vector<Point> active_points;

    for (int i = 0; i < n; ++i) {
        Point p = points[i];
        int current_block = i / block_size;
        active_points.clear();

        for (int b = max(0, current_block - 1); b <= current_block; ++b) {
            if (b >= blocks.size()) continue;
            auto& block = blocks[b];
            long long lower_y = p.y - min_dist;
            long long upper_y = p.y + min_dist;
            auto it_low = lower_bound(block.begin(), block.end(), Point{0, lower_y});
            auto it_high = upper_bound(block.begin(), block.end(), Point{0, upper_y});

            for (auto it = it_low; it != it_high; ++it) {
                active_points.push_back(*it);
            }
        }

        sort(active_points.begin(), active_points.end(), [&](const Point& a, const Point& b) {
            return (a.x - p.x) * (a.x - p.x) + (a.y - p.y) * (a.y - p.y) <
                   (b.x - p.x) * (b.x - p.x) + (b.y - p.y) * (b.y - p.y);
        });

        for (int j = 0; j < min(7, (int)active_points.size()); ++j) {
            if (active_points[j].x == p.x && active_points[j].y == p.y) continue;
            double dx = p.x - active_points[j].x;
            double dy = p.y - active_points[j].y;
            double dist = sqrt(dx * dx + dy * dy);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
    }

    return min_dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        double result = closest_pair(points);
        cout << fixed << setprecision(4) << result << '\n';
    }

    return 0;
}
