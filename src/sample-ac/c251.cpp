#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 40000;
int segMask[4*MAXN];
int segLazy[4*MAXN]; // -1 means no pending assignment

void build(int node, int l, int r) {
    segMask[node] = 0;
    segLazy[node] = -1;
    if (l == r) return;
    int m = (l+r)/2;
    build(2*node, l, m);
    build(2*node+1, m+1, r);
}

inline void applyTag(int node, int v) {
    segLazy[node] = v;
    segMask[node] = (v == 0) ? 0 : (1 << v);
}

inline void pushDown(int node) {
    if (segLazy[node] != -1) {
        int v = segLazy[node];
        applyTag(2*node, v);
        applyTag(2*node+1, v);
        segLazy[node] = -1;
    }
}

void update(int node, int l, int r, int ql, int qr, int v) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        applyTag(node, v);
        return;
    }
    pushDown(node);
    int m = (l+r)/2;
    update(2*node, l, m, ql, qr, v);
    update(2*node+1, m+1, r, ql, qr, v);
    segMask[node] = segMask[2*node] | segMask[2*node+1];
}

int query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return segMask[node];
    pushDown(node);
    int m = (l+r)/2;
    return query(2*node, l, m, ql, qr) | query(2*node+1, m+1, r, ql, qr);
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int N, Q;
        scanf("%d %d", &N, &Q);
        build(1, 1, N);
        while (Q--) {
            int K;
            scanf("%d", &K);
            if (K == 1) {
                int L, R, P;
                scanf("%d %d %d", &L, &R, &P);
                update(1, 1, N, L, R, P);
            } else {
                int L, R;
                scanf("%d %d", &L, &R);
                int m = query(1, 1, N, L, R);
                int cnt = __builtin_popcount((unsigned int)m);
                printf("%d\n", cnt);
            }
        }
    }
    return 0;
}
