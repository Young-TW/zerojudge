#include <bits/stdc++.h>
using namespace std;

struct Node {
    int lc, rc;          // leftmost colour, rightmost colour
    int seg;             // number of colour segments in the interval
    int lazy;            // 0 = none, otherwise whole interval becomes this colour
};

const int MAXN = 500000 + 5;
static Node segtree[4 * MAXN];
static int initArr[MAXN];

int N, Cc;                     // N beads, Cc colours (C c is not used further)

Node mergeNode(const Node& L, const Node& R) {
    Node res;
    res.lc = L.lc;
    res.rc = R.rc;
    res.seg = L.seg + R.seg - (L.rc == R.lc ? 1 : 0);
    res.lazy = 0;
    return res;
}

void build(int idx, int l, int r) {
    segtree[idx].lazy = 0;
    if (l == r) {
        segtree[idx].lc = segtree[idx].rc = initArr[l];
        segtree[idx].seg = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1, l, mid);
    build(idx << 1 | 1, mid + 1, r);
    segtree[idx] = mergeNode(segtree[idx << 1], segtree[idx << 1 | 1]);
}

inline void applyLazy(int idx, int colour) {
    segtree[idx].lc = segtree[idx].rc = colour;
    segtree[idx].seg = 1;
    segtree[idx].lazy = colour;
}

inline void pushDown(int idx) {
    if (segtree[idx].lazy) {
        applyLazy(idx << 1, segtree[idx].lazy);
        applyLazy(idx << 1 | 1, segtree[idx].lazy);
        segtree[idx].lazy = 0;
    }
}

void rangeAssign(int idx, int l, int r, int ql, int qr, int colour) {
    if (ql <= l && r <= qr) {
        applyLazy(idx, colour);
        return;
    }
    pushDown(idx);
    int mid = (l + r) >> 1;
    if (ql <= mid) rangeAssign(idx << 1, l, mid, ql, qr, colour);
    if (qr >  mid) rangeAssign(idx << 1 | 1, mid + 1, r, ql, qr, colour);
    segtree[idx] = mergeNode(segtree[idx << 1], segtree[idx << 1 | 1]);
}

Node queryRange(int idx, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return segtree[idx];
    pushDown(idx);
    int mid = (l + r) >> 1;
    if (qr <= mid) return queryRange(idx << 1, l, mid, ql, qr);
    if (ql >  mid) return queryRange(idx << 1 | 1, mid + 1, r, ql, qr);
    Node left = queryRange(idx << 1, l, mid, ql, qr);
    Node right = queryRange(idx << 1 | 1, mid + 1, r, ql, qr);
    return mergeNode(left, right);
}

/* ---------- logical ↔ physical mapping ---------- */
static long long baseIdx = 0;   // physical index of logical position 1 (0‑based)
static int dir = 1;            // +1 : normal order, -1 : reversed

inline int physIdx(int logicalPos) {          // logicalPos is 1‑based
    long long pos = baseIdx + (long long)dir * (logicalPos - 1);
    pos %= N;
    if (pos < 0) pos += N;
    return (int)pos;
}

/* return up to two linear intervals that together represent the logical
   clockwise segment [i … j] (both inclusive, 1‑based) */
static vector<pair<int,int>> getIntervals(int i, int j) {
    int start = physIdx(i);
    int end   = physIdx(j);
    vector<pair<int,int>> res;
    if (dir == 1) {
        if (start <= end) {
            res.emplace_back(start, end);
        } else {
            res.emplace_back(start, N - 1);
            res.emplace_back(0, end);
        }
    } else { // dir == -1
        // logical walk goes backwards, treat as forward [end … start]
        if (end <= start) {
            res.emplace_back(end, start);
        } else {
            res.emplace_back(end, N - 1);
            res.emplace_back(0, start);
        }
    }
    return res;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N >> Cc) {
        for (int i = 0; i < N; ++i) cin >> initArr[i];
        build(1, 0, N - 1);
        baseIdx = 0;
        dir = 1;

        int Q;
        cin >> Q;
        while (Q--) {
            string cmd;
            cin >> cmd;
            if (cmd == "R") {                     // Rotate k
                int k; cin >> k;
                baseIdx = (baseIdx - (long long)dir * k) % N;
                if (baseIdx < 0) baseIdx += N;
            } else if (cmd == "F") {              // Flip
                dir = -dir;
            } else if (cmd == "S") {              // Swap i j
                int i, j; cin >> i >> j;
                int p = physIdx(i);
                int q = physIdx(j);
                if (p == q) continue;
                int colP = queryRange(1, 0, N - 1, p, p).lc;
                int colQ = queryRange(1, 0, N - 1, q, q).lc;
                if (colP != colQ) {
                    rangeAssign(1, 0, N - 1, p, p, colQ);
                    rangeAssign(1, 0, N - 1, q, q, colP);
                }
            } else if (cmd == "P") {              // Paint i j x
                int i, j, x; cin >> i >> j >> x;
                auto intervals = getIntervals(i, j);
                for (auto &pr : intervals) {
                    rangeAssign(1, 0, N - 1, pr.first, pr.second, x);
                }
            } else if (cmd == "C") {              // Count whole circle
                if (N == 1) {
                    cout << 1 << '\n';
                } else {
                    Node root = segtree[1];
                    int ans = root.seg;
                    if (root.lc == root.rc && root.seg > 1) ans--;
                    cout << ans << '\n';
                }
            } else if (cmd == "CS") {             // CountSegment i j
                int i, j; cin >> i >> j;
                auto intervals = getIntervals(i, j);
                Node cur = queryRange(1, 0, N - 1, intervals[0].first, intervals[0].second);
                for (size_t idx = 1; idx < intervals.size(); ++idx) {
                    Node nxt = queryRange(1, 0, N - 1, intervals[idx].first, intervals[idx].second);
                    cur.seg = cur.seg + nxt.seg - (cur.rc == nxt.lc ? 1 : 0);
                    cur.rc = nxt.rc;
                }
                cout << cur.seg << '\n';
            }
        }
    }
    return 0;
}
