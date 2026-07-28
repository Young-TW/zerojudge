#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Node {
    int mn, smn, cnt_mn, cnt_smn;
    Node() : mn(0), smn(INF), cnt_mn(0), cnt_smn(0) {}
    Node(int _mn, int _smn, int _cmn, int _csmn)
        : mn(_mn), smn(_smn), cnt_mn(_cmn), cnt_smn(_csmn) {}
};

Node combine(const Node& a, const Node& b) {
    int mn_val = min(a.mn, b.mn);
    int cnt_mn_val = 0;
    if (a.mn == mn_val) cnt_mn_val += a.cnt_mn;
    if (b.mn == mn_val) cnt_mn_val += b.cnt_mn;

    int smn_val = INF;
    int cnt_smn_val = 0;

    auto consider = [&](int val, int cnt) {
        if (val == INF) return;
        if (val > mn_val) {
            if (val < smn_val) {
                smn_val = val;
                cnt_smn_val = cnt;
            } else if (val == smn_val) {
                cnt_smn_val += cnt;
            }
        }
    };

    consider(a.mn, a.cnt_mn);
    consider(a.smn, a.cnt_smn);
    consider(b.mn, b.cnt_mn);
    consider(b.smn, b.cnt_smn);

    return Node(mn_val, smn_val, cnt_mn_val, cnt_smn_val);
}

class SegmentTree {
    int n;
    vector<Node> tree;
    vector<int> lazy;

public:
    SegmentTree(int _n) : n(_n) {
        tree.resize(4 * n + 5);
        lazy.resize(4 * n + 5);
        build(1, 1, n);
    }

    void build(int node, int l, int r) {
        tree[node] = Node(0, INF, r - l + 1, 0);
        lazy[node] = 0;
        if (l == r) return;
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
    }

    void apply(int node, int delta) {
        tree[node].mn += delta;
        if (tree[node].smn != INF) tree[node].smn += delta;
        lazy[node] += delta;
    }

    void push(int node) {
        if (lazy[node] != 0) {
            apply(node * 2, lazy[node]);
            apply(node * 2 + 1, lazy[node]);
            lazy[node] = 0;
        }
    }

    void pull(int node) {
        tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int ql, int qr, int delta) {
        if (ql <= l && r <= qr) {
            apply(node, delta);
            return;
        }
        push(node);
        int mid = (l + r) / 2;
        if (ql <= mid) update(node * 2, l, mid, ql, qr, delta);
        if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, delta);
        pull(node);
    }

    int query(int node, int l, int r, int ql, int qr, int k) {
        if (ql <= l && r <= qr) {
            if (tree[node].mn == k) return tree[node].cnt_mn;
            if (tree[node].smn == k) return tree[node].cnt_smn;
            return 0;
        }
        push(node);
        int mid = (l + r) / 2;
        int res = 0;
        if (ql <= mid) res += query(node * 2, l, mid, ql, qr, k);
        if (qr > mid) res += query(node * 2 + 1, mid + 1, r, ql, qr, k);
        return res;
    }

    void range_add(int l, int r, int delta) {
        if (l > r) return;
        update(1, 1, n, l, r, delta);
    }

    int query_equal(int l, int r, int k) {
        if (l > r) return 0;
        return query(1, 1, n, l, r, k);
    }
};

struct Event {
    int l, r, delta;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        vector<int> a(n + 1), c(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> c[i];

        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }

        vector<int> posC(n + 1);
        for (int i = 1; i <= n; ++i) posC[c[i]] = i;
        vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) p[i] = posC[a[i]];
        vector<int> inv_p(n + 1);
        for (int i = 1; i <= n; ++i) inv_p[p[i]] = i;

        vector<vector<Event>> events(n + 2);
        for (int v = 1; v <= n; ++v) {
            int u = (v == n ? 1 : v + 1);
            int x = inv_p[v];
            int y = inv_p[u];
            int a = min(x, y);
            int b = max(x, y);
            events[a].push_back({1, a, 1});
            events[b].push_back({1, a, -1});
            if (a + 1 <= b) events[b].push_back({a + 1, b, 1});
        }

        SegmentTree seg(n);
        long long ans = 0;
        for (int r = 1; r <= n; ++r) {
            for (auto& ev : events[r]) {
                seg.range_add(ev.l, ev.r, ev.delta);
            }
            ans += seg.query_equal(1, r, 2);
        }
        ans += 1; // full set
        cout << ans << '\n';
    }
    return 0;
}
