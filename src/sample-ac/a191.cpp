#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

struct Point {
    int x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        vector<int> max_dist(N, 0);
        for (int i = 0; i < N; ++i) {
            int current_max = 0;
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                int dx = points[i].x - points[j].x;
                int dy = points[i].y - points[j].y;
                int dist = dx * dx + dy * dy;
                if (dist > current_max) {
                    current_max = dist;
                }
            }
            max_dist[i] = current_max;
        }

        for (int i = 0; i < N; ++i) {
            cout << max_dist[i] << '\n';
        }
    }

    return 0;
}
