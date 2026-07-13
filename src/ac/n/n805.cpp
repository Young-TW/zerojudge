#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct SegTree {
    int n;
    vector<int> tree;
    int INF;
    SegTree(int size, int inf_val) : n(size), INF(inf_val) {
        tree.assign(4 * n, INF);
    }
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = min(tree[node], val);
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(node * 2, l, mid, idx, val);
        else update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return INF;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return min(query(node * 2, l, mid, ql, qr),
                   query(node * 2 + 1, mid + 1, r, ql, qr));
    }
    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }
    int query(int l, int r) { 
        if (l > r) return INF;
        return query(1, 0, n - 1, l, r); 
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long K;
    while (cin >> N >> K) {
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        vector<long long> vals = A;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int M = vals.size();
        
        const int INF = N + 5;
        SegTree st(M, INF);
        vector<int> ans(N, -1);
        
        for (int i = N - 1; i >= 0; --i) {
            long long threshold = A[i] + K;
            int l = lower_bound(vals.begin(), vals.end(), threshold) - vals.begin();
            if (l < M) {
                int minIdx = st.query(l, M - 1);
                if (minIdx != INF) {
                    ans[i] = minIdx + 1;
                }
            }
            int pos = lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin();
            st.update(pos, i);
        }
        
        for (int i = 0; i < N; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
