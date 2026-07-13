#include <cstdio>
#include <algorithm>

using namespace std;

struct Node {
    long long sum;
    long long pre;
};

const int MAXN = 200005;
Node tree[4 * MAXN];
long long arr[MAXN];

Node mergeNode(const Node& a, const Node& b) {
    Node res;
    res.sum = a.sum + b.sum;
    res.pre = min(a.pre, a.sum + b.pre);
    return res;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = arr[start];
        tree[node].pre = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    tree[node] = mergeNode(tree[node * 2], tree[node * 2 + 1]);
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node].sum = val;
        tree[node].pre = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(node * 2, start, mid, idx, val);
    } else {
        update(node * 2 + 1, mid + 1, end, idx, val);
    }
    tree[node] = mergeNode(tree[node * 2], tree[node * 2 + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    if (r <= mid) {
        return query(node * 2, start, mid, l, r);
    } else if (l > mid) {
        return query(node * 2 + 1, mid + 1, end, l, r);
    } else {
        return mergeNode(query(node * 2, start, mid, l, r), query(node * 2 + 1, mid + 1, end, l, r));
    }
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        for (int i = 1; i <= N; ++i) {
            scanf("%lld", &arr[i]);
        }
        build(1, 1, N);
        int Q;
        scanf("%d", &Q);
        while (Q--) {
            int t;
            scanf("%d", &t);
            if (t == 1) {
                int p;
                long long val;
                scanf("%d %lld", &p, &val);
                update(1, 1, N, p, val);
            } else if (t == 2) {
                int l, r;
                scanf("%d %d", &l, &r);
                Node res = query(1, 1, N, l, r);
                long long ans = max(1LL, -res.pre + 1);
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
