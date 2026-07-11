#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005;

long long tree[MAXN * 4];
long long lazy[MAXN * 4];

void pushup(int node) {
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

void pushdown(int node) {
    if (lazy[node] != 0) {
        tree[node * 2] += lazy[node];
        lazy[node * 2] += lazy[node];
        tree[node * 2 + 1] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void build(int node, int l, int r, const vector<long long>& P) {
    lazy[node] = 0;
    if (l == r) {
        tree[node] = -P[l - 1];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid, P);
    build(node * 2 + 1, mid + 1, r, P);
    pushup(node);
}

void update(int node, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) {
        tree[node] += val;
        lazy[node] += val;
        return;
    }
    pushdown(node);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        update(node * 2, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
    }
    pushup(node);
}

long long query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[node];
    }
    pushdown(node);
    int mid = (l + r) / 2;
    long long res = -1e18;
    if (ql <= mid) {
        res = max(res, query(node * 2, l, mid, ql, qr));
    }
    if (qr > mid) {
        res = max(res, query(node * 2 + 1, mid + 1, r, ql, qr));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        vector<long long> a(n + 1);
        vector<long long> P(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            P[i] = P[i - 1] + a[i];
        }

        vector<vector<pair<int, long long>>> pairs(n + 1);
        for (int i = 0; i < m; ++i) {
            int b, c;
            long long d;
            cin >> b >> c >> d;
            pairs[c].push_back({b, d});
        }

        build(1, 1, n, P);

        long long ans = -1e18;
        for (int r = 1; r <= n; ++r) {
            for (const auto& p : pairs[r]) {
                update(1, 1, n, 1, p.first, p.second);
            }
            long long max_val = query(1, 1, n, 1, r);
            ans = max(ans, P[r] + max_val);
        }

        cout << ans << "\n";
    }

    return 0;
}
