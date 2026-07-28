#include <bits/stdc++.h>
using namespace std;

const int MAXQ = 100005;

int n, q;
struct Op {
    int ty, l, r, h, id;
} ops[MAXQ];

int cancel_time[MAXQ]; // cancel_time[i] = time when operation i is cancelled, or q+1 if never cancelled

// Time segment tree
vector<int> time_tree[4*MAXQ]; // stores indices of type-1 operations

void addOp(int node, int l, int r, int ql, int qr, int op_idx) {
    if (ql <= l && r <= qr) {
        time_tree[node].push_back(op_idx);
        return;
    }
    int mid = (l+r)/2;
    if (ql <= mid) addOp(2*node, l, mid, ql, qr, op_idx);
    if (qr > mid) addOp(2*node+1, mid+1, r, ql, qr, op_idx);
}

// Position segment tree with rollback
int pos_tree[12*MAXQ]; // 3 values per node (mx, mn, lazy), 4*n nodes
vector<pair<int,int>> history;

void write(int idx, int val) {
    history.push_back({idx, pos_tree[idx]});
    pos_tree[idx] = val;
}

void applyMax(int node, int h) {
    int base = 3*node;
    if (h > pos_tree[base]) write(base, h);
    if (h > pos_tree[base+1]) write(base+1, h);
    if (h > pos_tree[base+2]) write(base+2, h);
}

void pushdown(int node) {
    int lazy = pos_tree[3*node+2];
    if (lazy > 0) {
        applyMax(2*node, lazy);
        applyMax(2*node+1, lazy);
    }
}

void pullup(int node) {
    int new_mx = max(pos_tree[3*(2*node)], pos_tree[3*(2*node+1)]);
    int new_mn = min(pos_tree[3*(2*node)+1], pos_tree[3*(2*node+1)+1]);
    if (new_mx != pos_tree[3*node]) write(3*node, new_mx);
    if (new_mn != pos_tree[3*node+1]) write(3*node+1, new_mn);
}

void update(int node, int l, int r, int ql, int qr, int h) {
    if (ql <= l && r <= qr) {
        applyMax(node, h);
        return;
    }
    pushdown(node);
    int mid = (l+r)/2;
    if (ql <= mid) update(2*node, l, mid, ql, qr, h);
    if (qr > mid) update(2*node+1, mid+1, r, ql, qr, h);
    pullup(node);
}

int queryMax(int node, int l, int r, int ql, int qr, int carry) {
    if (ql <= l && r <= qr) {
        return max(pos_tree[3*node], carry);
    }
    int mid = (l+r)/2;
    int new_carry = max(carry, pos_tree[3*node+2]);
    int res = 0;
    if (ql <= mid) res = max(res, queryMax(2*node, l, mid, ql, qr, new_carry));
    if (qr > mid) res = max(res, queryMax(2*node+1, mid+1, r, ql, qr, new_carry));
    return res;
}

int queryMin(int node, int l, int r, int ql, int qr, int carry) {
    if (ql <= l && r <= qr) {
        return max(pos_tree[3*node+1], carry);
    }
    int mid = (l+r)/2;
    int new_carry = max(carry, pos_tree[3*node+2]);
    int res = INT_MAX;
    if (ql <= mid) res = min(res, queryMin(2*node, l, mid, ql, qr, new_carry));
    if (qr > mid) res = min(res, queryMin(2*node+1, mid+1, r, ql, qr, new_carry));
    return res;
}

void rollback(size_t target) {
    while (history.size() > target) {
        pos_tree[history.back().first] = history.back().second;
        history.pop_back();
    }
}

// Queries
vector<tuple<int,int,int>> queries[MAXQ]; // (l, r, type) for each time, type 3=max, 4=min
int ans[MAXQ];

void dfs(int node, int l, int r) {
    size_t checkpoint = history.size();
    
    // Apply all operations at this node
    for (int op_idx : time_tree[node]) {
        update(1, 1, n, ops[op_idx].l, ops[op_idx].r, ops[op_idx].h);
    }
    
    if (l == r) {
        // Answer queries at time l
        for (auto& [ql, qr, ty] : queries[l]) {
            if (ty == 3) {
                ans[l] = queryMax(1, 1, n, ql, qr, 0);
            } else {
                ans[l] = queryMin(1, 1, n, ql, qr, 0);
            }
        }
    } else {
        int mid = (l+r)/2;
        dfs(2*node, l, mid);
        dfs(2*node+1, mid+1, r);
    }
    
    rollback(checkpoint);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> q;
    
    for (int i = 1; i <= q; i++) {
        cancel_time[i] = q+1; // default: never cancelled
    }
    
    for (int i = 1; i <= q; i++) {
        cin >> ops[i].ty;
        if (ops[i].ty == 1) {
            cin >> ops[i].l >> ops[i].r >> ops[i].h;
        } else if (ops[i].ty == 2) {
            cin >> ops[i].id;
            cancel_time[ops[i].id] = i;
        } else {
            cin >> ops[i].l >> ops[i].r;
        }
    }
    
    // Add type-1 operations to time segment tree
    for (int i = 1; i <= q; i++) {
        if (ops[i].ty == 1) {
            int ct = cancel_time[i];
            // Active during [i, ct-1]
            if (i <= ct-1) {
                addOp(1, 1, q, i, ct-1, i);
            }
        }
    }
    
    // Collect queries
    for (int i = 1; i <= q; i++) {
        if (ops[i].ty == 3 || ops[i].ty == 4) {
            queries[i].push_back({ops[i].l, ops[i].r, ops[i].ty});
        }
    }
    
    // Initialize position segment tree
    memset(pos_tree, 0, sizeof(pos_tree));
    
    // DFS
    dfs(1, 1, q);
    
    // Output answers
    for (int i = 1; i <= q; i++) {
        if (ops[i].ty == 3 || ops[i].ty == 4) {
            cout << ans[i] << '\n';
        }
    }
    
    return 0;
}
