#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

static const int MAXN = 100005;
static const int MAXNODES = MAXN * 22;

static int lc[MAXNODES], rc[MAXNODES], sum[MAXNODES];
static int root[MAXN];
static int nodeCnt;

int build(int l, int r) {
    int cur = ++nodeCnt;
    sum[cur] = 0;
    if (l == r) return cur;
    int mid = (l + r) >> 1;
    lc[cur] = build(l, mid);
    rc[cur] = build(mid + 1, r);
    return cur;
}

int update(int prev, int l, int r, int pos) {
    int cur = ++nodeCnt;
    lc[cur] = lc[prev];
    rc[cur] = rc[prev];
    sum[cur] = sum[prev] + 1;
    if (l == r) return cur;
    int mid = (l + r) >> 1;
    if (pos <= mid) lc[cur] = update(lc[prev], l, mid, pos);
    else rc[cur] = update(rc[prev], mid + 1, r, pos);
    return cur;
}

int query(int u, int v, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int cnt = sum[lc[v]] - sum[lc[u]];
    if (k <= cnt) return query(lc[u], lc[v], l, mid, k);
    else return query(rc[u], rc[v], mid + 1, r, k - cnt);
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        int sz = (int)b.size();
        nodeCnt = 0;
        root[0] = build(1, sz);
        for (int i = 0; i < n; i++) {
            int pos = (int)(lower_bound(b.begin(), b.end(), a[i]) - b.begin()) + 1;
            root[i + 1] = update(root[i], 1, sz, pos);
        }
        while (m--) {
            int i, j, k;
            scanf("%d %d %d", &i, &j, &k);
            int idx = query(root[i - 1], root[j], 1, sz, k);
            printf("%d\n", b[idx - 1]);
        }
    }
    return 0;
}
