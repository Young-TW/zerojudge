#include <iostream>
#include <vector>

using namespace std;

void build(int node, int start, int end, const vector<int>& arr, vector<long long>& tree) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr, tree);
        build(2 * node + 1, mid + 1, end, arr, tree);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void update(int node, int start, int end, int idx, long long val, vector<long long>& tree) {
    if (start == end) {
        tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val, tree);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val, tree);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

int query(int node, int start, int end, long long k, const vector<long long>& tree) {
    if (start == end) {
        return start;
    }
    int mid = (start + end) / 2;
    if (tree[2 * node] >= k) {
        return query(2 * node, start, mid, k, tree);
    } else {
        return query(2 * node + 1, mid + 1, end, k - tree[2 * node], tree);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    while (cin >> n >> q) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        vector<long long> tree(4 * n + 5);
        build(1, 1, n, a, tree);

        for (int i = 0; i < q; ++i) {
            int t;
            cin >> t;
            if (t == 1) {
                int p;
                long long c;
                cin >> p >> c;
                update(1, 1, n, p, c, tree);
            } else if (t == 2) {
                long long k;
                cin >> k;
                if (tree[1] < k) {
                    cout << "meh\n";
                } else {
                    cout << query(1, 1, n, k, tree) << "\n";
                }
            }
        }
    }

    return 0;
}
