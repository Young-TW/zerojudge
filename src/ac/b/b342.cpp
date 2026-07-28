#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <array>
#include <utility>
using namespace std;

struct BIT2D {
    int n;
    vector<vector<int> > ys;
    vector<vector<int> > bit;
    
    BIT2D(int n = 0) : n(n) {
        ys.resize(n + 1);
        bit.resize(n + 1);
    }
    
    void fake_update(int x, int y) {
        for (int i = x; i <= n; i += i & -i)
            ys[i].push_back(y);
    }
    
    void build() {
        for (int i = 1; i <= n; ++i) {
            auto &v = ys[i];
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            bit[i].assign(v.size() + 1, 0);
        }
    }
    
    void add(int x, int y, int delta) {
        for (int i = x; i <= n; i += i & -i) {
            int j = lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin() + 1;
            for (; j < (int)bit[i].size(); j += j & -j)
                bit[i][j] += delta;
        }
    }
    
    int sum(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            int j = upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin();
            for (; j > 0; j -= j & -j)
                res += bit[i][j];
        }
        return res;
    }
};

struct Node {
    int a, b, c, d;
    int idx;
    int ans;
};

void cdq(int l, int r, vector<Node>& nodes, BIT2D& bit) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid, nodes, bit);
    cdq(mid + 1, r, nodes, bit);
    
    vector<int> order(r - l + 1);
    iota(order.begin(), order.end(), l);
    sort(order.begin(), order.end(), [&](int i, int j) {
        if (nodes[i].b != nodes[j].b) return nodes[i].b < nodes[j].b;
        if ((i <= mid) != (j <= mid)) return (i <= mid);
        return i < j;
    });
    
    for (int id : order) {
        if (id <= mid) {
            bit.add(nodes[id].c, nodes[id].d, 1);
        } else {
            nodes[id].ans += bit.sum(nodes[id].c, nodes[id].d);
        }
    }
    
    for (int id : order) {
        if (id <= mid) {
            bit.add(nodes[id].c, nodes[id].d, -1);
        }
    }
}

struct SegTree {
    int n;
    vector<multiset<pair<int, int> > > tree;
    
    SegTree(int n) : n(n) {
        tree.resize(4 * n);
    }
    
    void update(int node, int l, int r, int ql, int qr, int depth, int idx) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node].insert({-depth, idx});
            return;
        }
        int mid = (l + r) >> 1;
        update(node << 1, l, mid, ql, qr, depth, idx);
        update(node << 1 | 1, mid + 1, r, ql, qr, depth, idx);
    }
    
    void erase(int node, int l, int r, int ql, int qr, int depth, int idx) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node].erase({-depth, idx});
            return;
        }
        int mid = (l + r) >> 1;
        erase(node << 1, l, mid, ql, qr, depth, idx);
        erase(node << 1 | 1, mid + 1, r, ql, qr, depth, idx);
    }
    
    pair<int, int> query(int node, int l, int r, int pos) {
        pair<int, int> best = {-1, -1};
        if (!tree[node].empty()) {
            auto it = tree[node].begin();
            best = {-it->first, it->second};
        }
        if (l == r) return best;
        int mid = (l + r) >> 1;
        pair<int, int> child;
        if (pos <= mid) child = query(node << 1, l, mid, pos);
        else child = query(node << 1 | 1, mid + 1, r, pos);
        if (child.first > best.first || (child.first == best.first && child.second < best.second))
            best = child;
        return best;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<array<int, 4> > rects(N);
        for (int i = 0; i < N; ++i) {
            cin >> rects[i][0] >> rects[i][1] >> rects[i][2] >> rects[i][3];
        }
        int M;
        cin >> M;
        vector<pair<int, int> > queries(M);
        for (int i = 0; i < M; ++i) {
            cin >> queries[i].first >> queries[i].second;
        }
        
        // ---------- 計算矩形深度 ----------
        vector<Node> nodes(N);
        vector<int> allC, allD;
        for (int i = 0; i < N; ++i) {
            int lx = rects[i][0], ly = rects[i][1], rx = rects[i][2], ry = rects[i][3];
            nodes[i].a = lx;
            nodes[i].b = ly;
            nodes[i].c = -rx;
            nodes[i].d = -ry;
            nodes[i].idx = i;
            nodes[i].ans = 0;
            allC.push_back(nodes[i].c);
            allD.push_back(nodes[i].d);
        }
        
        sort(allC.begin(), allC.end());
        allC.erase(unique(allC.begin(), allC.end()), allC.end());
        sort(allD.begin(), allD.end());
        allD.erase(unique(allD.begin(), allD.end()), allD.end());
        
        auto getC = [&](int v) {
            return lower_bound(allC.begin(), allC.end(), v) - allC.begin() + 1;
        };
        auto getD = [&](int v) {
            return lower_bound(allD.begin(), allD.end(), v) - allD.begin() + 1;
        };
        
        for (int i = 0; i < N; ++i) {
            nodes[i].c = getC(nodes[i].c);
            nodes[i].d = getD(nodes[i].d);
        }
        
        BIT2D bit(allC.size());
        for (int i = 0; i < N; ++i) {
            bit.fake_update(nodes[i].c, nodes[i].d);
        }
        bit.build();
        
        sort(nodes.begin(), nodes.end(), [](const Node& p, const Node& q) {
            if (p.a != q.a) return p.a < q.a;
            if (p.b != q.b) return p.b < q.b;
            if (p.c != q.c) return p.c < q.c;
            if (p.d != q.d) return p.d < q.d;
            return p.idx < q.idx;
        });
        
        cdq(0, N - 1, nodes, bit);
        
        vector<int> height(N);
        for (const auto& nd : nodes) {
            height[nd.idx] = nd.ans + 1;
        }
        
        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << ' ';
            cout << height[i];
        }
        cout << '\n';
        
        // ---------- 點查詢 ----------
        vector<int> allY;
        for (int i = 0; i < N; ++i) {
            allY.push_back(rects[i][1]);
            allY.push_back(rects[i][3]);
        }
        for (int i = 0; i < M; ++i) {
            allY.push_back(queries[i].second);
        }
        sort(allY.begin(), allY.end());
        allY.erase(unique(allY.begin(), allY.end()), allY.end());
        
        auto getY = [&](int y) {
            return lower_bound(allY.begin(), allY.end(), y) - allY.begin();
        };
        
        struct Event {
            int x, type, y1, y2, depth, idx;
        };
        vector<Event> events;
        for (int i = 0; i < N; ++i) {
            int lx = rects[i][0], rx = rects[i][2];
            int ly_idx = getY(rects[i][1]);
            int ry_idx = getY(rects[i][3]);
            int d = height[i] - 1;
            events.push_back({lx, 1, ly_idx, ry_idx, d, i});
            events.push_back({rx + 1, 0, ly_idx, ry_idx, d, i});
        }
        for (int i = 0; i < M; ++i) {
            int x = queries[i].first;
            int y_idx = getY(queries[i].second);
            events.push_back({x, 2, y_idx, -1, 0, i});
        }
        
        sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
            if (e1.x != e2.x) return e1.x < e2.x;
            return e1.type < e2.type;
        });
        
        SegTree seg(allY.size());
        vector<int> ansQuery(M, -1);
        
        for (const auto& ev : events) {
            if (ev.type == 0) {
                seg.erase(1, 0, allY.size() - 1, ev.y1, ev.y2, ev.depth, ev.idx);
            } else if (ev.type == 1) {
                seg.update(1, 0, allY.size() - 1, ev.y1, ev.y2, ev.depth, ev.idx);
            } else {
                auto res = seg.query(1, 0, allY.size() - 1, ev.y1);
                if (res.first != -1) {
                    ansQuery[ev.idx] = res.second;
                }
            }
        }
        
        for (int i = 0; i < M; ++i) {
            cout << ansQuery[i] << '\n';
        }
    }
    return 0;
}
