#include <bits/stdc++.h>
using namespace std;

/* ---------- 2‑D segment tree, range maximum, point update ---------- */
class SegTree2D {
    int n, m;                                   // dimensions
    vector< vector<int> > tree;                 // tree[outer][inner]

    /* inner tree point update (max) */
    void updateY(int nodeX, int nodeY, int ly, int ry,
                 int y, int val) {
        if (ly == ry) {
            tree[nodeX][nodeY] = max(tree[nodeX][nodeY], val);
            return;
        }
        int my = (ly + ry) >> 1;
        if (y <= my) updateY(nodeX, nodeY << 1, ly, my, y, val);
        else          updateY(nodeX, nodeY << 1 | 1, my + 1, ry, y, val);
        tree[nodeX][nodeY] = max(tree[nodeX][nodeY << 1],
                                 tree[nodeX][nodeY << 1 | 1]);
    }

    /* outer tree point update – after reaching the leaf we also
       update the inner tree of every visited outer node                */
    void updateX(int nodeX, int lx, int rx,
                 int x, int y, int val) {
        updateY(nodeX, 1, 1, m, y, val);
        if (lx != rx) {
            int mx = (lx + rx) >> 1;
            if (x <= mx) updateX(nodeX << 1, lx, mx, x, y, val);
            else          updateX(nodeX << 1 | 1, mx + 1, rx, x, y, val);
        }
    }

    /* inner tree query (range maximum) */
    int queryY(int nodeX, int nodeY, int ly, int ry,
               int y1, int y2) const {
        if (y1 > ry || y2 < ly) return 0;
        if (y1 <= ly && ry <= y2) return tree[nodeX][nodeY];
        int my = (ly + ry) >> 1;
        return max(queryY(nodeX, nodeY << 1, ly, my, y1, y2),
                   queryY(nodeX, nodeY << 1 | 1, my + 1, ry, y1, y2));
    }

    /* outer tree query – rectangle (x1..x2 , y1..y2) */
    int queryX(int nodeX, int lx, int rx,
               int x1, int x2, int y1, int y2) const {
        if (x1 > rx || x2 < lx) return 0;
        if (x1 <= lx && rx <= x2) return queryY(nodeX, 1, 1, m, y1, y2);
        int mx = (lx + rx) >> 1;
        return max(queryX(nodeX << 1, lx, mx, x1, x2, y1, y2),
                   queryX(nodeX << 1 | 1, mx + 1, rx, x1, x2, y1, y2));
    }

public:
    SegTree2D(int n_, int m_) : n(n_), m(m_) {
        tree.assign(4 * n + 4, vector<int>(4 * m + 4, 0));
    }
    void update(int x, int y, int val) { updateX(1, 1, n, x, y, val); }

    // query rectangle [x1..x2] × [y1..y2]; returns 0 if empty or out of range
    int query(int x1, int x2, int y1, int y2) const {
        if (x1 > x2 || y1 > y2) return 0;
        int xx1 = max(x1, 1), xx2 = min(x2, n);
        int yy1 = max(y1, 1), yy2 = min(y2, m);
        if (xx1 > xx2 || yy1 > yy2) return 0;
        return queryX(1, 1, n, xx1, xx2, yy1, yy2);
    }
};

/* ------------------------------- main ------------------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    if (!(cin >> a >> b)) return 0;
    int N = (int)a.size();
    int M = (int)b.size();

    int K;
    cin >> K;

    const int INF = 1000;                 // larger than any possible gap
    vector<int> answers;

    for (int tc = 0; tc < K; ++tc) {
        array<int,26> gap;
        gap.fill(INF);

        string token;
        while (cin >> token) {
            if (token == "$") break;
            char ch = token[0];
            int val; cin >> val;
            gap[ch - 'A'] = val;
        }

        SegTree2D seg(N, M);
        int bestAns = 0;

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                int cur = 0;
                if (a[i-1] == b[j-1]) {
                    int g = gap[a[i-1] - 'A'];
                    int x1 = i - g - 1;
                    int y1 = j - g - 1;
                    if (x1 < 1) x1 = 1;
                    if (y1 < 1) y1 = 1;
                    int bestPrev = seg.query(x1, i-1, y1, j-1);
                    cur = bestPrev + 1;
                    if (cur > bestAns) bestAns = cur;
                }
                seg.update(i, j, cur);               // also stores 0 for non‑matches
            }
        }
        answers.push_back(bestAns);
    }

    for (size_t i = 0; i < answers.size(); ++i) {
        if (i) cout << ' ';
        cout << answers[i];
    }
    cout << '\n';
    return 0;
}
