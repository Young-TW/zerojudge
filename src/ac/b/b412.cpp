#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l, r;
    int val;
    Node(int _l = 0, int _r = 0, int _v = 0) : l(_l), r(_r), val(_v) {}
};

/* ---------- persistent segment tree for one array ---------- */
struct PersistentSeg {
    vector<Node> seg;
    int n;

    PersistentSeg(int _n = 0) { init(_n); }

    void init(int _n) {
        n = _n;
        seg.clear();
        seg.reserve((_n + 5) * 40);
    }

    int build(int l, int r, bool isParent) {
        int idx = (int)seg.size();
        seg.emplace_back();
        if (l == r) {
            seg[idx].val = isParent ? l : 1;   // parent[l]=l , size[l]=1
        } else {
            int mid = (l + r) >> 1;
            seg[idx].l = build(l, mid, isParent);
            seg[idx].r = build(mid + 1, r, isParent);
        }
        return idx;
    }

    int update(int node, int l, int r, int pos, int value) {
        int idx = (int)seg.size();
        seg.push_back(seg[node]);               // copy
        if (l == r) {
            seg[idx].val = value;
        } else {
            int mid = (l + r) >> 1;
            if (pos <= mid)
                seg[idx].l = update(seg[node].l, l, mid, pos, value);
            else
                seg[idx].r = update(seg[node].r, mid + 1, r, pos, value);
        }
        return idx;
    }

    int query(int node, int l, int r, int pos) const {
        if (l == r) return seg[node].val;
        int mid = (l + r) >> 1;
        if (pos <= mid) return query(seg[node].l, l, mid, pos);
        else            return query(seg[node].r, mid + 1, r, pos);
    }
};

/* ---------- persistent DSU using two segment trees ---------- */
int n, m;
PersistentSeg pstParent, pstSize;
vector<int> rootPar, rootSz;   // roots for each day (0 … m)

int find_root(int x, int rootParIdx) {
    int p = pstParent.query(rootParIdx, 1, n, x);
    if (p == x) return x;
    return find_root(p, rootParIdx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n >> m)) return 0;

    pstParent.init(n);
    pstSize.init(n);
    int rootPar0 = pstParent.build(1, n, true);   // parent[i]=i
    int rootSize0 = pstSize.build(1, n, false);   // size[i]=1

    rootPar.assign(m + 1, 0);
    rootSz.assign(m + 1, 0);
    rootPar[0] = rootPar0;
    rootSz[0] = rootSize0;

    int ans = 0;
    for (int d = 1; d <= m; ++d) {
        int t_enc;  cin >> t_enc;
        int t = t_enc ^ ans;

        if (t == 0) {                     // rollback
            int k_enc;  cin >> k_enc;
            int k = k_enc ^ ans;
            rootPar[d] = rootPar[k];
            rootSz[d]  = rootSz[k];
        }
        else if (t == 1) {                // union
            int x_enc, y_enc;
            cin >> x_enc >> y_enc;
            int x = x_enc ^ ans;
            int y = y_enc ^ ans;

            int curPar = rootPar[d - 1];
            int curSz  = rootSz[d - 1];

            int rx = find_root(x, curPar);
            int ry = find_root(y, curPar);
            if (rx != ry) {
                int szx = pstSize.query(curSz, 1, n, rx);
                int szy = pstSize.query(curSz, 1, n, ry);
                if (szx < szy) {
                    swap(rx, ry);
                    swap(szx, szy);
                }
                curPar = pstParent.update(curPar, 1, n, ry, rx);
                curSz  = pstSize.update(curSz, 1, n, rx, szx + szy);
            }
            rootPar[d] = curPar;
            rootSz[d]  = curSz;
        }
        else {                            // query
            int x_enc, y_enc;
            cin >> x_enc >> y_enc;
            int x = x_enc ^ ans;
            int y = y_enc ^ ans;

            int curPar = rootPar[d - 1];
            int curSz  = rootSz[d - 1];   // unchanged, only to keep the pair

            int rx = find_root(x, curPar);
            int ry = find_root(y, curPar);
            ans = (rx == ry) ? 1 : 0;
            cout << ans << '\n';

            rootPar[d] = curPar;
            rootSz[d]  = curSz;
        }
    }
    return 0;
}
