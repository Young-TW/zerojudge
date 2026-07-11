#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, r;
    while (cin >> N >> r) {
        vector<pair<int, int>> offsets;
        for (int dx = -r; dx <= r; ++dx) {
            for (int dy = -r; dy <= r; ++dy) {
                if (dx * dx + dy * dy <= r * r) {
                    offsets.push_back({dx, dy});
                }
            }
        }

        vector<long long> points;
        points.reserve(N * offsets.size());

        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            for (const auto& off : offsets) {
                int nx = x + off.first;
                int ny = y + off.second;
                points.push_back((long long)(nx + 2000000) * 4000000LL + (ny + 2000000));
            }
        }

        sort(points.begin(), points.end());

        long long ans = 0;
        if (!points.empty()) {
            int count = 1;
            for (size_t i = 1; i < points.size(); ++i) {
                if (points[i] == points[i - 1]) {
                    count++;
                } else {
                    if (count % 2 == 1) {
                        ans++;
                    }
                    count = 1;
                }
            }
            if (count % 2 == 1) {
                ans++;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
