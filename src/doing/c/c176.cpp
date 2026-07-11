#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const long long INF = 1e18;

struct Node {
    long long sum;
    long long min_val;
    long long max_val;
    long long lazy_add;
    bool has_lazy;
    
    Node() : sum(0), min_val(0), max_val(0), lazy_add(0), has_lazy(false) {}
};

int n;
vector<long long> arr;
vector<Node> tree;

void push_up(int node) {
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].min_val = min(tree[node * 2].min_val, tree[node * 2 + 1].min_val);
    tree[node].max_val = max(tree[node * 2].max_val, tree[node * 2 + 1].max_val);
}

void push_down(int node, int l, int r) {
    if (!tree[node].has_lazy) return;
    
    int mid = (l + r) / 2;
    int left_child = node * 2;
    int right_child = node * 2 + 1;
    
    long long add_val = tree[node].lazy_add;
    
    tree[left_child].lazy_add += add_val;
    tree[left_child].has_lazy = true;
    tree[left_child].sum += add_val * (mid - l + 1);
    tree[left_child].min_val += add_val;
    tree[left_child].max_val += add_val;
    
    tree[right_child].lazy_add += add_val;
    tree[right_child].has_lazy = true;
    tree[right_child].sum += add_val * (r - mid);
    tree[right_child].min_val += add_val;
    tree[right_child].max_val += add_val;
    
    tree[node].lazy_add = 0;
    tree[node].has_lazy = false;
}

void build(int node, int l, int r) {
    tree[node].lazy_add = 0;
    tree[node].has_lazy = false;
    
    if (l == r) {
        long long val = arr[l];
        tree[node].sum = val;
        tree[node].min_val = val;
        tree[node].max_val = val;
        return;
    }
    
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    push_up(node);
}

void update_range(int node, int l, int r, int ql, int qr, long long val) {
    if (ql > r || qr < l) return;
    
    if (ql <= l && r <= qr) {
        tree[node].lazy_add += val;
        tree[node].has_lazy = true;
        tree[node].sum += val * (r - l + 1);
        tree[node].min_val += val;
        tree[node].max_val += val;
        return;
    }
    
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node * 2, l, mid, ql, qr, val);
    update_range(node * 2 + 1, mid + 1, r, ql, qr, val);
    push_up(node);
}

long long query_sum(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    
    if (ql <= l && r <= qr) {
        return tree[node].sum;
    }
    
    push_down(node, l, r);
    int mid = (l + r) / 2;
    return query_sum(node * 2, l, mid, ql, qr) + 
           query_sum(node * 2 + 1, mid + 1, r, ql, qr);
}

int find_first_negative(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l || tree[node].min_val >= 0) {
        return -1;
    }
    
    if (l == r) {
        return l;
    }
    
    push_down(node, l, r);
    int mid = (l + r) / 2;
    
    int left_result = find_first_negative(node * 2, l, mid, ql, qr);
    if (left_result != -1) {
        return left_result;
    }
    
    return find_first_negative(node * 2 + 1, mid + 1, r, ql, qr);
}

void clamp_negatives(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l || tree[node].min_val >= 0) {
        return;
    }
    
    if (l == r) {
        if (tree[node].min_val < 0) {
            long long diff = -tree[node].min_val;
            tree[node].sum = 0;
            tree[node].min_val = 0;
            tree[node].max_val = 0;
        }
        return;
    }
    
    push_down(node, l, r);
    int mid = (l + r) / 2;
    clamp_negatives(node * 2, l, mid, ql, qr);
    clamp_negatives(node * 2 + 1, mid + 1, r, ql, qr);
    push_up(node);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    if (!(cin >> n >> k)) return 0;
    
    arr.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    tree.resize(4 * n + 10);
    build(1, 1, n);
    
    char op;
    int i, j;
    long long x;
    
    while (k--) {
        cin >> op;
        if (op == 'C') {
            cin >> i >> j;
            cout << query_sum(1, 1, n, i, j) << "\n";
        } else {
            cin >> i >> j >> x;
            if (op == '+') {
                update_range(1, 1, n, i, j, x);
            } else if (op == '-') {
                update_range(1, 1, n, i, j, -x);
                
                while (true) {
                    int pos = find_first_negative(1, 1, n, i, j);
                    if (pos == -1) break;
                    
                    long long current_val;
                    int l = 1, r = n;
                    int node = 1;
                    
                    vector<int> path;
                    int cur_node = 1, cur_l = 1, cur_r = n;
                    while (cur_l != cur_r) {
                        push_down(cur_node, cur_l, cur_r);
                        int mid = (cur_l + cur_r) / 2;
                        if (pos <= mid) {
                            cur_node = cur_node * 2;
                            cur_r = mid;
                        } else {
                            cur_node = cur_node * 2 + 1;
                            cur_l = mid + 1;
                        }
                    }
                    current_val = tree[cur_node].min_val;
                    
                    long long diff = -current_val;
                    update_range(1, 1, n, pos, pos, diff);
                }
            }
        }
    }
    
    return 0;
}
