#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 20005;
int tree[MAXN * 4];

struct Frustum {
    int R, r, h;
};

void build(int node, int l, int r) {
    tree[node] = 0;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
}

void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        tree[node] = max(tree[node], val);
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) update(node * 2, l, mid, idx, val);
    else update(node * 2 + 1, mid + 1, r, idx, val);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    return max(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
}

int main() {
    int N;
    vector<Frustum> f(10005);
    vector<int> vals;
    vals.reserve(20005);
    
    while (scanf("%d", &N) != EOF) {
        if (N == 0) {
            printf("0\n");
            continue;
        }
        vals.clear();
        for (int i = 0; i < N; ++i) {
            scanf("%d %d %d", &f[i].R, &f[i].r, &f[i].h);
            vals.push_back(f[i].R);
            vals.push_back(f[i].r);
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int M = vals.size();
        for (int i = 0; i < N; ++i) {
            f[i].R = lower_bound(vals.begin(), vals.end(), f[i].R) - vals.begin() + 1;
            f[i].r = lower_bound(vals.begin(), vals.end(), f[i].r) - vals.begin() + 1;
        }
        sort(f.begin(), f.begin() + N, [](const Frustum& a, const Frustum& b) {
            if (a.R != b.R) return a.R > b.R;
            return a.r > b.r;
        });
        build(1, 1, M);
        for (int i = 0; i < N; ++i) {
            int max_h = query(1, 1, M, f[i].R, M);
            update(1, 1, M, f[i].r, max_h + f[i].h);
        }
        printf("%d\n", query(1, 1, M, 1, M));
    }
    return 0;
}
