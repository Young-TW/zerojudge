#include <bits/stdc++.h>
using namespace std;

struct Tree {
    long long dist;   // squared distance from (0,0)
    int h;            // height
    bool isStart;
    bool isEnd;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<Tree> a;
        a.reserve(N);
        for (int i = 0; i < N; ++i) {
            long long x, y;
            int h;
            cin >> x >> y >> h;
            Tree t;
            t.dist = x * x + y * y;
            t.h = h;
            t.isStart = (x == 0 && y == 0);
            t.isEnd   = (x == 10000 && y == 10000);
            a.push_back(t);
        }

        // sort by distance asc, height desc (so higher trees of same distance first)
        sort(a.begin(), a.end(), [](const Tree& A, const Tree& B) {
            if (A.dist != B.dist) return A.dist < B.dist;
            if (A.isStart != B.isStart) return A.isStart;   // start first if same distance
            return A.h > B.h;                               // higher first
        });

        long long maxHeightSeen = -1;   // no tree processed yet
        long long answer = 0;

        for (const auto& t : a) {
            if (maxHeightSeen >= 0) {
                long long cand = maxHeightSeen - t.h;
                if (cand > answer) answer = cand;
            }
            if (t.h > maxHeightSeen) maxHeightSeen = t.h;
        }

        cout << answer << '\n';
    }
    return 0;
}
