#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <climits>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
    int id;               // original position in input
};

struct Node {
    int idx;              // index in points vector
    int left, right;      // children indices in tree vector
    int xmin, xmax, ymin, ymax;   // bounding box of the subtree
};

static vector<Point> pts;          // points (may be reordered)
static vector<Node> tree;          // kd‑tree nodes

// squared distance of two points
inline int64_t dist2(const Point& a, const Point& b) {
    int64_t dx = int64_t(a.x) - b.x;
    int64_t dy = int64_t(a.y) - b.y;
    return dx * dx + dy * dy;
}

// maximal possible squared distance from p to any point inside node's box
inline int64_t maxDistBox(const Point& p, const Node& nd) {
    int64_t dx = std::max( std::abs(int64_t(p.x) - nd.xmin),
                           std::abs(int64_t(p.x) - nd.xmax) );
    int64_t dy = std::max( std::abs(int64_t(p.y) - nd.ymin),
                           std::abs(int64_t(p.y) - nd.ymax) );
    return dx * dx + dy * dy;
}

// build kd‑tree on pts[l..r] (inclusive), depth indicates splitting dimension
int build(int l, int r, int depth) {
    if (l > r) return -1;
    int dim = depth & 1;               // 0 → x , 1 → y
    int m = (l + r) >> 1;
    nth_element(pts.begin() + l, pts.begin() + m, pts.begin() + r + 1,
        [dim](const Point& a, const Point& b) {
            return dim ? a.y < b.y : a.x < b.x;
        });
    Node nd;
    nd.idx = m;
    nd.left = build(l, m - 1, depth + 1);
    nd.right = build(m + 1, r, depth + 1);

    // initialise bounding box with own point
    nd.xmin = nd.xmax = pts[m].x;
    nd.ymin = nd.ymax = pts[m].y;

    // expand with children boxes
    if (nd.left != -1) {
        const Node& L = tree[nd.left];
        nd.xmin = std::min(nd.xmin, L.xmin);
        nd.xmax = std::max(nd.xmax, L.xmax);
        nd.ymin = std::min(nd.ymin, L.ymin);
        nd.ymax = std::max(nd.ymax, L.ymax);
    }
    if (nd.right != -1) {
        const Node& R = tree[nd.right];
        nd.xmin = std::min(nd.xmin, R.xmin);
        nd.xmax = std::max(nd.xmax, R.xmax);
        nd.ymin = std::min(nd.ymin, R.ymin);
        nd.ymax = std::max(nd.ymax, R.ymax);
    }

    tree.push_back(nd);
    return (int)tree.size() - 1;
}

// recursive farthest‑neighbour search
void query(int nodeIdx, const Point& p, int64_t& best) {
    if (nodeIdx == -1) return;
    const Node& nd = tree[nodeIdx];

    if (maxDistBox(p, nd) <= best) return;          // prune

    const Point& q = pts[nd.idx];
    if (q.id != p.id) {
        int64_t d = dist2(p, q);
        if (d > best) best = d;
    }

    int64_t leftBox  = (nd.left  == -1) ? -1 : maxDistBox(p, tree[nd.left]);
    int64_t rightBox = (nd.right == -1) ? -1 : maxDistBox(p, tree[nd.right]);

    // visit the more promising child first
    if (leftBox > rightBox) {
        if (leftBox > best)  query(nd.left,  p, best);
        if (rightBox > best) query(nd.right, p, best);
    } else {
        if (rightBox > best) query(nd.right, p, best);
        if (leftBox > best)  query(nd.left,  p, best);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        pts.resize(N);
        for (int i = 0; i < N; ++i) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].id = i;
        }

        tree.clear();
        tree.reserve(N);
        int root = build(0, N - 1, 0);

        vector<int64_t> answer(N, 0);
        for (int i = 0; i < N; ++i) {
            int64_t best = 0;
            query(root, pts[i], best);
            answer[pts[i].id] = best;
        }

        for (int i = 0; i < N; ++i) {
            cout << answer[i] << '\n';
        }
    }
    return 0;
}
