#include <iostream>
#include <algorithm>

using namespace std;

const long long INF = 1e9;

struct Node {
    long long v00, v01, v10, v11;
    Node() : v00(0), v01(-INF), v10(-INF), v11(-INF) {}
    Node(int x) {
        if (x == 1) {
            v00 = 0; v01 = -INF; v10 = -INF; v11 = 1;
        } else {
            v00 = 0; v01 = -INF; v10 = -INF; v11 = -INF;
        }
    }
};

Node merge(const Node& a, const Node& b) {
    Node c;
    c.v00 = max({a.v00 + b.v00, a.v00 + b.v10, a.v01 + b.v00});
    c.v01 = max({a.v00 + b.v01, a.v00 + b.v11, a.v01 + b.v01});
    c.v10 = max({a.v10 + b.v00, a.v10 + b.v10, a.v11 + b.v00});
    c.v11 = max({a.v10 + b.v01, a.v10 + b.v11, a.v11 + b.v01});
    return c;
}

const int MAXN = 100005;
Node tree[4 * MAXN];
int arr[MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = Node(arr[start]);
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[start] = val;
        tree[node] = Node(val);
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
}

Node query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    if (r <= mid) {
        return query(2 * node, start, mid, l, r);
    } else if (l > mid) {
        return query(2 * node + 1, mid + 1, end, l, r);
    } else {
        Node p1 = query(2 * node, start, mid, l, r);
        Node p2 = query(2 * node + 1, mid + 1, end, l, r);
        return merge(p1, p2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while (cin >> n >> q) {
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        build(1, 1, n);
        while (q--) {
            int ty;
            cin >> ty;
            if (ty == 1) {
                int p;
                cin >> p;
                update(1, 1, n, p, 1 - arr[p]);
            } else {
                int l, r;
                cin >> l >> r;
                Node res = query(1, 1, n, l, r);
                cout << max({res.v00, res.v01, res.v10, res.v11}) << "\n";
            }
        }
    }
    return 0;
}
