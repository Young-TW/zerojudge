#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> tails;
};

vector<Node> seg;

void merge_into(vector<int>& G, const vector<int>& R) {
    int p = 0;
    for (int x : R) {
        while (p < (int)G.size() && G[p] < x) ++p;
        if (p == (int)G.size()) {
            G.push_back(x);
        } else {
            G[p] = x;
        }
    }
}

void build(int idx, int l, int r, const vector<int>& a) {
    if (l == r) {
        seg[idx].tails = {a[l]};
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1, l, mid, a);
    build(idx << 1 | 1, mid + 1, r, a);
    seg[idx].tails = seg[idx << 1].tails;
    merge_into(seg[idx].tails, seg[idx << 1 | 1].tails);
}

void query(int idx, int l, int r, int ql, int qr, vector<int>& res) {
    if (ql <= l && r <= qr) {
        merge_into(res, seg[idx].tails);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) query(idx << 1, l, mid, ql, qr, res);
    if (qr > mid) query(idx << 1 | 1, mid + 1, r, ql, qr, res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while (cin >> n >> q) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        seg.assign(4 * n + 4, Node());
        build(1, 1, n, a);
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            vector<int> res;
            query(1, 1, n, l, r, res);
            cout << res.size() << '\n';
        }
    }
    return 0;
}
