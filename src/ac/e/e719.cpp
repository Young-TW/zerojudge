#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;          // we only need counts, int is enough (≤ N)
    Fenwick(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }
    // add delta at position idx (0‑based)
    void add(int idx, int delta) {
        for (int i = idx + 1; i <= n; i += i & -i) bit[i] += delta;
    }
    // prefix sum [0 .. idx] (0‑based), idx may be -1 → returns 0
    int sum(int idx) const {
        int res = 0;
        for (int i = idx + 1; i > 0; i -= i & -i) res += bit[i];
        return res;
    }
    // range sum [l .. r] (0‑based, l <= r)
    int rangeSum(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - (l ? sum(l - 1) : 0);
    }
};

struct Point {
    long long x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long R;
    int N;
    while (cin >> R >> N) {
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;

        if (R < 0) {                 // impossible range
            cout << 0 << '\n';
            continue;
        }

        // coordinate compression for y
        vector<long long> allY;
        allY.reserve(N);
        for (auto &p : pts) allY.push_back(p.y);
        sort(allY.begin(), allY.end());
        allY.erase(unique(allY.begin(), allY.end()), allY.end());

        auto yIndex = [&](long long y) {
            return (int)(lower_bound(allY.begin(), allY.end(), y) - allY.begin());
        };

        // sort by x
        sort(pts.begin(), pts.end(),
             [](const Point &a, const Point &b) {
                 if (a.x != b.x) return a.x < b.x;
                 return a.y < b.y;
             });

        Fenwick bit((int)allY.size());
        long long answer = 0;
        int left = 0;

        for (int i = 0; i < N; ++i) {
            long long curX = pts[i].x;
            long long curY = pts[i].y;

            // remove points too far on the left
            while (left < i && pts[left].x < curX - R) {
                bit.add(yIndex(pts[left].y), -1);
                ++left;
            }

            // query y in [curY - R , curY + R]
            long long lowY = curY - R;
            long long highY = curY + R;
            int l = (int)(lower_bound(allY.begin(), allY.end(), lowY) - allY.begin());
            int r = (int)(upper_bound(allY.begin(), allY.end(), highY) - allY.begin()) - 1;
            if (l <= r) {
                answer += bit.rangeSum(l, r);
            }

            // insert current point
            bit.add(yIndex(curY), +1);
        }

        cout << answer << '\n';
    }
    return 0;
}
