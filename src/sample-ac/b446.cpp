#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

int manhattan(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<Point> steph, sora;
        set<Point> steph_set, sora_set;

        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            steph.emplace_back(x, y);
            steph_set.insert(Point(x, y));

            if (i > 0) {
                int min_dist = INT_MAX;
                for (const auto& p : sora) {
                    int dist = manhattan(Point(x, y), p);
                    if (dist < min_dist) {
                        min_dist = dist;
                    }
                }
                cout << min_dist << '\n';
            }

            cin >> x >> y;
            sora.emplace_back(x, y);
            sora_set.insert(Point(x, y));

            int min_dist = INT_MAX;
            for (const auto& p : steph) {
                int dist = manhattan(Point(x, y), p);
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
            cout << min_dist << '\n';
        }
    }

    return 0;
}
