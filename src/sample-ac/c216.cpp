#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

const int MAXN = 100005;
const int MAXV = 100000;
const int MAXNODES = 2000005;

struct Node {
    int lc, rc;
    int cnt;
} tree[MAXNODES];

int root[MAXN];
int node_cnt = 0;
int arr[MAXN];
long long prefix[MAXN];

void insert(int &rt, int pre, int l, int r, int val) {
    rt = ++node_cnt;
    tree[rt] = tree[pre];
    tree[rt].cnt++;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    if (val <= mid) {
        insert(tree[rt].lc, tree[pre].lc, l, mid, val);
    } else {
        insert(tree[rt].rc, tree[pre].rc, mid + 1, r, val);
    }
}

int query(int rt, int pre, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[rt].cnt - tree[pre].cnt;
    int mid = l + (r - l) / 2;
    return query(tree[rt].lc, tree[pre].lc, l, mid, ql, qr) +
           query(tree[rt].rc, tree[pre].rc, mid + 1, r, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        node_cnt = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> arr[i];
            prefix[i] = prefix[i - 1] + arr[i];
            insert(root[i], root[i - 1], 1, MAXV, arr[i]);
        }

        int add = 0;
        while (m--) {
            int op;
            cin >> op;
            if (op == 1) {
                int k;
                cin >> k;
                add = (add + k) % MAXV;
            } else if (op == 2) {
                int L, R;
                cin >> L >> R;
                long long sum = prefix[R] - prefix[L - 1];
                sum += 1LL * add * (R - L + 1);
                int v = MAXV + 1 - add;
                if (add > 0) {
                    int cnt = query(root[R], root[L - 1], 1, MAXV, v, MAXV);
                    sum -= 1LL * MAXV * cnt;
                }
                cout << sum << "\n";
            }
        }
    }

    return 0;
}
