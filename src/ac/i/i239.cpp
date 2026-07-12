#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 200010;
int seg[MAXN * 4];

void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        seg[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) update(node * 2, l, mid, idx, val);
    else update(node * 2 + 1, mid + 1, r, idx, val);
    seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
}

int query(int node, int l, int r, int ql) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (seg[node * 2] < ql) return query(node * 2, l, mid, ql);
    else return query(node * 2 + 1, mid + 1, r, ql);
}

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return r < other.r;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    while (cin >> n >> q) {
        int max_val = n + 1;
        memset(seg, 0, sizeof(seg));
        
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        
        vector<Query> queries(q);
        for (int i = 0; i < q; ++i) {
            cin >> queries[i].l >> queries[i].r;
            queries[i].id = i;
        }
        
        sort(queries.begin(), queries.end());
        
        vector<int> ans(q);
        
        int q_idx = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] <= n) {
                update(1, 0, max_val, a[i], i);
            }
            while (q_idx < q && queries[q_idx].r == i) {
                ans[queries[q_idx].id] = query(1, 0, max_val, queries[q_idx].l);
                q_idx++;
            }
        }
        
        for (int i = 0; i < q; ++i) {
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
