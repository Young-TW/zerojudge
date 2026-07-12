#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int MAXNODE = MAXN * 25;

struct Node {
    int lc, rc;
    int min_pos;
};

Node tree[MAXNODE];
int root[MAXN];
int cnt;

int update(int pre, int l, int r, int pos, int val) {
    int u = ++cnt;
    tree[u] = tree[pre];
    if (l == r) {
        tree[u].min_pos = val;
        return u;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        tree[u].lc = update(tree[pre].lc, l, mid, pos, val);
    } else {
        tree[u].rc = update(tree[pre].rc, mid + 1, r, pos, val);
    }
    tree[u].min_pos = min(tree[tree[u].lc].min_pos, tree[tree[u].rc].min_pos);
    return u;
}

int query(int u, int l, int r, int ql) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (tree[tree[u].lc].min_pos < ql) {
        return query(tree[u].lc, l, mid, ql);
    } else {
        return query(tree[u].rc, mid + 1, r, ql);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    while (cin >> n >> q) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        
        cnt = 0;
        tree[0].lc = tree[0].rc = 0;
        tree[0].min_pos = 0;
        root[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            if (a[i] <= n) {
                root[i] = update(root[i - 1], 0, n, a[i], i);
            } else {
                root[i] = root[i - 1];
            }
        }
        
        int ans = 0;
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l ^= ans;
            r ^= ans;
            ans = query(root[r], 0, n, l);
            cout << ans << "\n";
        }
    }
    
    return 0;
}
