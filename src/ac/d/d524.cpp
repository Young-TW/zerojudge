#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Point {
    int r, c, idx;
    Point(int r = 0, int c = 0, int idx = 0) : r(r), c(c), idx(idx) {}
    bool operator<(const Point& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, case_num = 0;
    while (cin >> n >> m) {
        if (n == -1 && m == -1) break;
        vector<Point> points;
        points.emplace_back(1, 1, 0); // Start point
        int r, c, idx = 1;
        while (cin >> r >> c) {
            if (r == 0 && c == 0) break;
            points.emplace_back(r, c, idx++);
        }
        points.emplace_back(n, m, idx); // End point

        sort(points.begin(), points.end());

        int K = points.size();
        vector<int> dp(K, 0); // dp[i]: max garbage count to reach point i
        vector<long long> cnt(K, 0); // cnt[i]: number of paths to reach point i with max garbage
        vector<int> prev(K, -1); // prev[i]: predecessor index for path reconstruction

        for (int i = 0; i < K; ++i) {
            dp[i] = 0;
            cnt[i] = 0;
            prev[i] = -1;
            for (int j = 0; j < i; ++j) {
                if (points[j].r <= points[i].r && points[j].c <= points[i].c) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        cnt[i] = cnt[j];
                        prev[i] = j;
                    } else if (dp[j] + 1 == dp[i]) {
                        cnt[i] += cnt[j];
                    }
                }
            }
            if (dp[i] == 0) {
                dp[i] = 1; // At least the point itself
                cnt[i] = 1;
            }
        }

        vector<int> path;
        int cur = K - 1;
        while (cur != -1) {
            if (points[cur].idx != 0 && points[cur].idx != idx) {
                path.push_back(points[cur].idx);
            }
            cur = prev[cur];
        }
        reverse(path.begin(), path.end());

        cout << "CASE#" << ++case_num << ": " << path.size() << " " << cnt[K-1] << "\n";
    }

    return 0;
}
