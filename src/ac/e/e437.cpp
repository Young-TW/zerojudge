#include <iostream>
#include <algorithm>

using namespace std;

const int MaxN = 1000000 + 5;
const int MaxQ = 100000 + 5;
const int TreeSize = 1 << 21;

int A[MaxN];
bool C[MaxQ];
int X[MaxQ], Y[MaxQ], Z[MaxQ];
int k, m, N, Q;

void gen_dat() {
    int i, j;
    for (i = k + 1; i <= max(Q, N); ++i)
        A[i] = (A[i - 2] * 97 + A[i - 1] * 3) % m + 1;
    for (i = 1, j = max(Q, N); i <= Q; ++i, --j) {
        C[i] = A[i] & 1;
        X[i] = (A[i] + A[j]) % N + 1;
        Y[i] = X[i] + ((A[i] << 3) + (A[j] << 5) + m) % (N - X[i] + 1);
        if (!C[i]) Z[i] = ((A[i] << 3) + (A[j] << 5)) % m + 1;
    }
}

struct Node {
    int sum;
    int mx;
    int mn;
    int tag;
} tree[TreeSize];

void push_up(int node) {
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].mx = max(tree[node * 2].mx, tree[node * 2 + 1].mx);
    tree[node].mn = min(tree[node * 2].mn, tree[node * 2 + 1].mn);
}

void build(int node, int l, int r) {
    tree[node].tag = 0;
    if (l == r) {
        tree[node].sum = A[l];
        tree[node].mx = A[l];
        tree[node].mn = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    push_up(node);
}

void push_down(int node, int l, int r) {
    if (tree[node].tag != 0) {
        int mid = (l + r) / 2;
        int tag = tree[node].tag;
        
        tree[node * 2].tag = tag;
        tree[node * 2].sum = tag * (mid - l + 1);
        tree[node * 2].mx = tag;
        tree[node * 2].mn = tag;
        
        tree[node * 2 + 1].tag = tag;
        tree[node * 2 + 1].sum = tag * (r - mid);
        tree[node * 2 + 1].mx = tag;
        tree[node * 2 + 1].mn = tag;
        
        tree[node].tag = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[node].tag = val;
        tree[node].sum = val * (r - l + 1);
        tree[node].mx = val;
        tree[node].mn = val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        update(node * 2, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
    }
    push_up(node);
}

Node query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[node];
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (qr <= mid) {
        return query(node * 2, l, mid, ql, qr);
    } else if (ql > mid) {
        return query(node * 2 + 1, mid + 1, r, ql, qr);
    } else {
        Node left_res = query(node * 2, l, mid, ql, qr);
        Node right_res = query(node * 2 + 1, mid + 1, r, ql, qr);
        Node res;
        res.sum = left_res.sum + right_res.sum;
        res.mx = max(left_res.mx, right_res.mx);
        res.mn = min(left_res.mn, right_res.mn);
        res.tag = 0;
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> k >> m) {
        for (int i = 1; i <= k; ++i) {
            cin >> A[i];
        }
        cin >> N >> Q;
        gen_dat();
        build(1, 1, N);
        
        for (int i = 1; i <= Q; ++i) {
            if (C[i] == 0) {
                update(1, 1, N, X[i], Y[i], Z[i]);
            } else {
                Node res = query(1, 1, N, X[i], Y[i]);
                cout << res.sum % m << " " << res.mx - res.mn << "\n";
            }
        }
    }
    
    return 0;
}
