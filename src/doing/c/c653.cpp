#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Node {
    int min_val;
    int min_count;
    int lazy;
    bool is_lazy;
};

vector<Node> seg_tree;
vector<int> arr;

void build(int node, int start, int end) {
    if (start == end) {
        seg_tree[node].min_val = arr[start];
        seg_tree[node].min_count = 1;
        seg_tree[node].lazy = 0;
        seg_tree[node].is_lazy = false;
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        if (seg_tree[2 * node].min_val < seg_tree[2 * node + 1].min_val) {
            seg_tree[node].min_val = seg_tree[2 * node].min_val;
            seg_tree[node].min_count = seg_tree[2 * node].min_count;
        } else if (seg_tree[2 * node].min_val > seg_tree[2 * node + 1].min_val) {
            seg_tree[node].min_val = seg_tree[2 * node + 1].min_val;
            seg_tree[node].min_count = seg_tree[2 * node + 1].min_count;
        } else {
            seg_tree[node].min_val = seg_tree[2 * node].min_val;
            seg_tree[node].min_count = seg_tree[2 * node].min_count + seg_tree[2 * node + 1].min_count;
        }
    }
}

void push(int node, int start, int end) {
    if (seg_tree[node].is_lazy) {
        int val = seg_tree[node].lazy;
        seg_tree[node].min_val += val;
        if (start != end) {
            seg_tree[2 * node].lazy += val;
            seg_tree[2 * node].is_lazy = true;
            seg_tree[2 * node + 1].lazy += val;
            seg_tree[2 * node + 1].is_lazy = true;
        }
        seg_tree[node].is_lazy = false;
        seg_tree[node].lazy = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, int d) {
    push(node, start, end);
    if (start > r || end < l) return;
    if (l <= start && end <= r) {
        int min_val = seg_tree[node].min_val;
        int add = (d == 0) ? (2 * min_val) : (2 * min_val + 1);
        seg_tree[node].min_val += add;
        if (start != end) {
            seg_tree[2 * node].lazy += add;
            seg_tree[2 * node].is_lazy = true;
            seg_tree[2 * node + 1].lazy += add;
            seg_tree[2 * node + 1].is_lazy = true;
        }
        return;
    }
    int mid = (start + end) / 2;
    update_range(2 * node, start, mid, l, r, d);
    update_range(2 * node + 1, mid + 1, end, l, r, d);
    push(2 * node, start, mid);
    push(2 * node + 1, mid + 1, end);
    if (seg_tree[2 * node].min_val < seg_tree[2 * node + 1].min_val) {
        seg_tree[node].min_val = seg_tree[2 * node].min_val;
        seg_tree[node].min_count = seg_tree[2 * node].min_count;
    } else if (seg_tree[2 * node].min_val > seg_tree[2 * node + 1].min_val) {
        seg_tree[node].min_val = seg_tree[2 * node + 1].min_val;
        seg_tree[node].min_count = seg_tree[2 * node + 1].min_count;
    } else {
        seg_tree[node].min_val = seg_tree[2 * node].min_val;
        seg_tree[node].min_count = seg_tree[2 * node].min_count + seg_tree[2 * node + 1].min_count;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        arr.assign(N, 0);
        if (N > 0) {
            seg_tree.resize(4 * N);
            build(1, 0, N - 1);
        }

        for (int i = 0; i < Q; ++i) {
            int L, R, D;
            cin >> L >> R >> D;
            L--; R--;
            if (N > 0) {
                update_range(1, 0, N - 1, L, R, D);
            }
        }

        if (N == 0) {
            cout << "0\n";
            continue;
        }

        vector<int> final_arr(N);
        for (int i = 0; i < N; ++i) {
            final_arr[i] = 0;
        }

        if (N > 0) {
            for (int i = 0; i < N; ++i) {
                int node = 1;
                int start = 0, end = N - 1;
                while (start != end) {
                    push(node, start, end);
                    int mid = (start + end) / 2;
                    if (i <= mid) {
                        node = 2 * node;
                        end = mid;
                    } else {
                        node = 2 * node + 1;
                        start = mid + 1;
                    }
                }
                push(node, start, end);
                final_arr[i] = seg_tree[node].min_val;
            }
        }

        int odd = 0, even = 0;
        for (int num : final_arr) {
            if (num % 2 == 1) {
                odd++;
            } else {
                even++;
            }
        }
        cout << abs(odd - even) << '\n';
    }
    return 0;
}
