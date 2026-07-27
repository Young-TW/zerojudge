#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

const int INF = 1e9;

int n, K;
vector<Point> pt;

/* ---------- area of a mask ---------- */
int area_of_mask(uint64_t mask) {
    int minx = INF, maxx = -INF, miny = INF, maxy = -INF;
    for (int i = 0; i < n; ++i) if (mask & (1ULL << i)) {
        minx = min(minx, pt[i].x);
        maxx = max(maxx, pt[i].x);
        miny = min(miny, pt[i].y);
        maxy = max(maxy, pt[i].y);
    }
    return (maxx - minx) * (maxy - miny);
}

/* ---------- memoisation ---------- */
unordered_map<uint64_t, array<int,5>> memo;

/* ---------- recursive DP ---------- */
int solve(uint64_t mask, int cnt) {
    if (mask == 0) return 0;          // no points
    if (cnt == 0) return INF;        // impossible

    auto it = memo.find(mask);
    if (it == memo.end()) {
        array<int,5> a;
        a.fill(-1);
        it = memo.emplace(mask, a).first;
    }
    if (it->second[cnt] != -1) return it->second[cnt];

    int best = INF;

    /* use a single rectangle for the whole set */
    if (cnt >= 1) best = area_of_mask(mask);   // remaining rectangles may be empty

    /* collect indices of points in this mask */
    vector<int> idx;
    idx.reserve(__builtin_popcountll(mask));
    for (int i = 0; i < n; ++i)
        if (mask & (1ULL << i)) idx.push_back(i);
    int m = (int)idx.size();
    if (m == 1) {                     // single point, already handled by the line above
        it->second[cnt] = best;
        return best;
    }

    /* ---------- vertical splits ---------- */
    vector<int> idxX = idx;
    sort(idxX.begin(), idxX.end(),
         [&](int a, int b){ return pt[a].x < pt[b].x; });

    vector<int> prefMaxX(m), suffMinX(m);
    vector<uint64_t> prefMask(m);
    uint64_t curMask = 0;
    int curMax = -INF;
    for (int i = 0; i < m; ++i) {
        curMax = max(curMax, pt[idxX[i]].x);
        prefMaxX[i] = curMax;
        curMask |= (1ULL << idxX[i]);
        prefMask[i] = curMask;
    }
    int curMin = INF;
    for (int i = m - 1; i >= 0; --i) {
        curMin = min(curMin, pt[idxX[i]].x);
        suffMinX[i] = curMin;
    }

    for (int i = 0; i < m - 1; ++i) {
        if (prefMaxX[i] < suffMinX[i + 1]) {          // a gap exists
            uint64_t leftMask = prefMask[i];
            uint64_t rightMask = mask ^ leftMask;
            for (int t = 1; t <= cnt - 1; ++t) {
                int v1 = solve(leftMask, t);
                if (v1 == INF) continue;
                int v2 = solve(rightMask, cnt - t);
                if (v2 == INF) continue;
                best = min(best, v1 + v2);
            }
        }
    }

    /* ---------- horizontal splits ---------- */
    vector<int> idxY = idx;
    sort(idxY.begin(), idxY.end(),
         [&](int a, int b){ return pt[a].y < pt[b].y; });

    vector<int> prefMaxY(m), suffMinY(m);
    vector<uint64_t> prefMaskY(m);
    curMask = 0;
    curMax = -INF;
    for (int i = 0; i < m; ++i) {
        curMax = max(curMax, pt[idxY[i]].y);
        prefMaxY[i] = curMax;
        curMask |= (1ULL << idxY[i]);
        prefMaskY[i] = curMask;
    }
    curMin = INF;
    for (int i = m - 1; i >= 0; --i) {
        curMin = min(curMin, pt[idxY[i]].y);
        suffMinY[i] = curMin;
    }

    for (int i = 0; i < m - 1; ++i) {
        if (prefMaxY[i] < suffMinY[i + 1]) {
            uint64_t leftMask = prefMaskY[i];
            uint64_t rightMask = mask ^ leftMask;
            for (int t = 1; t <= cnt - 1; ++t) {
                int v1 = solve(leftMask, t);
                if (v1 == INF) continue;
                int v2 = solve(rightMask, cnt - t);
                if (v2 == INF) continue;
                best = min(best, v1 + v2);
            }
        }
    }

    it->second[cnt] = best;
    return best;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> K) {
        pt.assign(n, {});
        for (int i = 0; i < n; ++i) cin >> pt[i].x >> pt[i].y;
        memo.clear();
        uint64_t allMask = (n == 64) ? ~0ULL : ((1ULL << n) - 1);
        int ans = solve(allMask, K);
        cout << ans << '\n';
    }
    return 0;
}
