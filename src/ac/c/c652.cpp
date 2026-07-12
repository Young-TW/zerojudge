#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long isqrt(long long x) {
    if (x <= 0) return 0;
    long long r = (long long)sqrtl((long double)x);
    while (r * r > x) r--;
    while ((r + 1) * (r + 1) <= x) r++;
    return r;
}

struct Node {
    long long sum;
    long long mx;
};

vector<Node> tree;
vector<long long> arr;

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = arr[start];
        tree[node].mx = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
        tree[node].mx = max(tree[2 * node].mx, tree[2 * node + 1].mx);
    }
}

void update_sqrt(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return;
    }
    if (l <= start && end <= r) {
        if (tree[node].mx <= 1) {
            return;
        }
        if (start == end) {
            tree[node].sum = isqrt(tree[node].sum);
            tree[node].mx = tree[node].sum;
            return;
        }
    }
    int mid = (start + end) / 2;
    update_sqrt(2 * node, start, mid, l, r);
    update_sqrt(2 * node + 1, mid + 1, end, l, r);
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    tree[node].mx = max(tree[2 * node].mx, tree[2 * node + 1].mx);
}

long long query_sum(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return tree[node].sum;
    }
    int mid = (start + end) / 2;
    return query_sum(2 * node, start, mid, l, r) + query_sum(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    while (cin >> N >> Q) {
        arr.assign(N + 1, 0);
        tree.assign(4 * N + 5, {0, 0});
        for (int i = 1; i <= N; ++i) {
            cin >> arr[i];
        }
        build(1, 1, N);
        for (int i = 0; i < Q; ++i) {
            int type, l, r;
            cin >> type >> l >> r;
            if (type == 0) {
                cout << query_sum(1, 1, N, l, r) << "\n";
            } else {
                update_sqrt(1, 1, N, l, r);
            }
        }
    }
    return 0;
}
