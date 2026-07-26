#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Frustum {
    int R, r, h;          // compressed indices will be stored later
};

struct SegTree {
    int n;
    vector<int> tree;    // max segment tree

    SegTree(int _n = 0) { init(_n); }

    void init(int _n) {
        n = _n;
        tree.assign(4 * n + 4, 0);
    }

    // point update: set position idx to max(old, val)
    void update(int idx, int val, int node, int l, int r) {
        if (l == r) {
            if (val > tree[node]) tree[node] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid) update(idx, val, node << 1, l, mid);
        else            update(idx, val, node << 1 | 1, mid + 1, r);
        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }
    void update(int idx, int val) { update(idx, val, 1, 1, n); }

    // range maximum query on [ql, qr]; if ql>qr returns 0
    int query(int ql, int qr, int node, int l, int r) const {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) >> 1;
        int left  = query(ql, qr, node << 1, l, mid);
        int right = query(ql, qr, node << 1 | 1, mid + 1, r);
        return max(left, right);
    }
    int query(int ql, int qr) const {
        if (ql > qr) return 0;
        return query(ql, qr, 1, 1, n);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<Frustum> a(N);
        vector<int> all;
        all.reserve(2 * N);
        for (int i = 0; i < N; ++i) {
            int R, r, h;
            cin >> R >> r >> h;
            a[i] = {R, r, h};
            all.push_back(R);
            all.push_back(r);
        }

        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());

        for (int i = 0; i < N; ++i) {
            a[i].R = lower_bound(all.begin(), all.end(), a[i].R) - all.begin() + 1;
            a[i].r = lower_bound(all.begin(), all.end(), a[i].r) - all.begin() + 1;
        }

        sort(a.begin(), a.end(), [](const Frustum& x, const Frustum& y) {
            if (x.R != y.R) return x.R > y.R;          // descending R
            return x.r > y.r;                          // tie‑breaker, any order works
        });

        int M = (int)all.size();
        SegTree seg(M);
        int answer = 0;

        for (const auto& f : a) {
            int best = seg.query(f.R + 1, M);          // strict greater
            int cur = best + f.h;
            if (cur > answer) answer = cur;
            seg.update(f.r, cur);
        }

        cout << answer << '\n';
    }
    return 0;
}
