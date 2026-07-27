#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    int step;          // 放置的回合 (1-indexed)
};

struct SegTree {
    int n;
    int INF;
    vector<int> tree;
    SegTree(int n = 0, int INF = 0) { init(n, INF); }
    void init(int N, int INFv) {
        n = N;
        INF = INFv;
        tree.assign(4 * n, INF);
    }
    void reset() { fill(tree.begin(), tree.end(), INF); }
    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid) update(node << 1, l, mid, idx, val);
        else update(node << 1 | 1, mid + 1, r, idx, val);
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
    }
    int query(int L, int R) {
        if (L > R) return INF;
        return query(1, 0, n - 1, L, R);
    }
    int query(int node, int l, int r, int L, int R) {
        if (R < l || r < L) return INF;
        if (L <= l && r <= R) return tree[node];
        int mid = (l + r) >> 1;
        return min(query(node << 1, l, mid, L, R),
                   query(node << 1 | 1, mid + 1, r, L, R));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].step = i + 1;          // 第 i+1 步放下
        }

        // 壓縮 y 座標
        vector<int> ys;
        ys.reserve(n);
        for (auto &p : pts) ys.push_back(p.y);
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        vector<int> yRank(n);
        for (int i = 0; i < n; ++i) {
            yRank[i] = lower_bound(ys.begin(), ys.end(), pts[i].y) - ys.begin();
        }

        // 依 x 排序，取得順序
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
             [&](int a, int b) { return pts[a].x < pts[b].x; });

        // 建立以 y 為索引的線段樹
        const int INF = n + 5;
        SegTree seg((int)ys.size(), INF);

        long long scoreA = 0, scoreB = 0;

        // 主迴圈 O(n^2 log n)
        for (int i = 0; i < n; ++i) {
            seg.reset();                       // 清空內部點資訊
            for (int j = i + 1; j < n; ++j) {
                int idx_i = order[i];
                int idx_j = order[j];
                int yi = yRank[idx_i];
                int yj = yRank[idx_j];
                int low = min(yi, yj) + 1;
                int high = max(yi, yj) - 1;

                int interiorMin = seg.query(low, high);   // 最早出現在矩形內的回合
                int add_time = max(pts[idx_i].step, pts[idx_j].step);
                int block_time = (interiorMin == INF) ? n + 1 : interiorMin;

                if (block_time > add_time) {
                    int L = add_time;
                    int R = block_time - 1;
                    // 奇數回合數
                    long long oddCnt = ( (R + 1) / 2 ) - ( L / 2 );
                    long long len = R - L + 1;
                    long long evenCnt = len - oddCnt;
                    scoreA += oddCnt;
                    scoreB += evenCnt;
                }

                // 把 j 本身加入，供之後更大的 j 使用
                int idx_add = order[j];
                seg.update(yRank[idx_add], pts[idx_add].step);
            }
        }

        cout << scoreA << ' ' << scoreB << '\n';
    }
    return 0;
}
