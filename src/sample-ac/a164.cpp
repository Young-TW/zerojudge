#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll NEG = -(1LL << 62);

struct Node {
    ll sum;       // total sum of segment
    ll pmax;      // max prefix sum
    int pend;     // ending index of chosen prefix (rightmost end)
    ll smax;      // max suffix sum
    int sstart;   // starting index of chosen suffix (leftmost start)
    ll best;      // max subarray sum in segment
    int bi;       // left index of best
    int bj;       // right index of best
};

int N, Q;
int A[200005];
Node seg[1 << 19];

Node makeLeaf(int idx, int val) {
    Node n;
    n.sum = val;
    n.pmax = val;
    n.pend = idx;
    n.smax = val;
    n.sstart = idx;
    n.best = val;
    n.bi = idx;
    n.bj = idx;
    return n;
}

// Compare prefix candidates: choose the one with larger pmax;
// tie -> smaller pend (leftmost end).
// Returns true if a is strictly preferred over b.
bool prefBetter(const Node& a, const Node& b) {
    if (a.pmax != b.pmax) return a.pmax > b.pmax;
    return a.pend < b.pend;
}

// Compare suffix candidates: choose larger smax;
// tie -> smaller sstart (leftmost start).
bool suffBetter(const Node& a, const Node& b) {
    if (a.smax != b.smax) return a.smax > b.smax;
    return a.sstart < b.sstart;
}

// Compare best subarray: larger best; tie -> smaller bi; tie -> smaller bj.
bool bestBetter(const Node& a, const Node& b) {
    if (a.best != b.best) return a.best > b.best;
    if (a.bi != b.bi) return a.bi < b.bi;
    return a.bj < b.bj;
}

Node merge(const Node& L, const Node& R) {
    Node n;
    n.sum = L.sum + R.sum;

    // prefix: either L's prefix, or L.sum + R's prefix
    Node pcand = L;  // pmax = L.pmax, pend = L.pend
    Node pcand2;
    pcand2.pmax = L.sum + R.pmax;
    pcand2.pend = R.pend;
    if (prefBetter(pcand2, pcand)) pcand = pcand2;
    n.pmax = pcand.pmax;
    n.pend = pcand.pend;

    // suffix: either R's suffix, or R.sum + L's suffix
    Node scand = R;
    Node scand2;
    scand2.smax = R.sum + L.smax;
    scand2.sstart = L.sstart;
    if (suffBetter(scand2, scand)) scand = scand2;
    n.smax = scand.smax;
    n.sstart = scand.sstart;

    // best: L.best, R.best, or L.suffix + R.prefix
    Node bcand = L;
    if (bestBetter(R, bcand)) bcand = R;
    Node bcand3;
    bcand3.best = L.smax + R.pmax;
    bcand3.bi = L.sstart;
    bcand3.bj = R.pend;
    if (bestBetter(bcand3, bcand)) bcand = bcand3;
    n.best = bcand.best;
    n.bi = bcand.bi;
    n.bj = bcand.bj;

    return n;
}

void build(int node, int l, int r) {
    if (l == r) {
        seg[node] = makeLeaf(l, A[l]);
        return;
    }
    int m = (l + r) >> 1;
    build(node << 1, l, m);
    build(node << 1 | 1, m + 1, r);
    seg[node] = merge(seg[node << 1], seg[node << 1 | 1]);
}

Node query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[node];
    int m = (l + r) >> 1;
    if (qr <= m) return query(node << 1, l, m, ql, qr);
    if (ql > m) return query(node << 1 | 1, m + 1, r, ql, qr);
    return merge(query(node << 1, l, m, ql, qr),
                 query(node << 1 | 1, m + 1, r, ql, qr));
}

int main() {
    int caseNo = 0;
    while (scanf("%d %d", &N, &Q) == 2) {
        for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
        build(1, 1, N);
        printf("Case %d:\n", ++caseNo);
        while (Q--) {
            int L, R;
            scanf("%d %d", &L, &R);
            Node res = query(1, 1, N, L, R);
            printf("%d %d %lld\n", res.bi, res.bj, res.best);
        }
    }
    return 0;
}
