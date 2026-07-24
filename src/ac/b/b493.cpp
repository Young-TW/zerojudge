#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 5;
const int LOG   = 17;                 // 2^16 = 65536 > 5e4

struct PSTNode {
    int l, r, sum;
    PSTNode(): l(0), r(0), sum(0) {}
};
static PSTNode seg[MAXN * 260];       // enough for N*log^2 N (≈13M)
static int segTot;

int pstUpdate(int prev, int l, int r, int pos) {
    int cur = ++segTot;
    seg[cur] = seg[prev];
    seg[cur].sum += 1;
    if (l != r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) seg[cur].l = pstUpdate(seg[prev].l, l, mid, pos);
        else            seg[cur].r = pstUpdate(seg[prev].r, mid + 1, r, pos);
    }
    return cur;
}
int pstQuery(int node, int l, int r, int K) {
    if (!node || K < l) return 0;
    if (r <= K) return seg[node].sum;
    int mid = (l + r) >> 1;
    int res = pstQuery(seg[node].l, l, mid, K);
    if (K > mid) res += pstQuery(seg[node].r, mid + 1, r, K);
    return res;
}

/* ---------- DSU ---------- */
int dsuPar[MAXN], dsuSize[MAXN];
int dsuFind(int x) {
    while (dsuPar[x] != x) {
        dsuPar[x] = dsuPar[dsuPar[x]];
        x = dsuPar[x];
    }
    return x;
}

/* ---------- Tree data ---------- */
int N, Q;
int A[MAXN];
vector<int> adj[MAXN];
int up[MAXN][LOG];
int depthArr[MAXN];
int pstRoot[MAXN];          // persistent segment tree root for path from global root
int maxVal;                // = N (A_i ≤ N)

void dfsReRoot(int start, int parent) {
    // iterative stack to avoid recursion depth problems
    static pair<int,int> stk[MAXN];
    int top = 0;
    stk[top++] = {start, parent};
    while (top) {
        auto curp = stk[--top];
        int cur = curp.first, p = curp.second;
        up[cur][0] = p;
        for (int i = 1; i < LOG; ++i)
            up[cur][i] = up[ up[cur][i-1] ][i-1];
        depthArr[cur] = (p == 0 ? 0 : depthArr[p] + 1);
        pstRoot[cur] = pstUpdate(p == 0 ? 0 : pstRoot[p], 1, maxVal, A[cur]);
        for (int nb : adj[cur]) {
            if (nb == p) continue;
            stk[top++] = {nb, cur};
        }
    }
}

/* ---------- LCA ---------- */
int lca(int u, int v) {
    if (depthArr[u] < depthArr[v]) swap(u, v);
    int diff = depthArr[u] - depthArr[v];
    for (int i = LOG - 1; i >= 0; --i)
        if (diff & (1 << i)) u = up[u][i];
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

/* ---------- Link operation ---------- */
void linkEdge(int X, int Y) {
    int repX = dsuFind(X), repY = dsuFind(Y);
    if (repX == repY) return;               // already connected
    // ensure repX is the larger component
    if (dsuSize[repX] < dsuSize[repY]) {
        swap(X, Y);
        swap(repX, repY);
    }
    // re‑root the smaller component at Y and attach to X
    dfsReRoot(Y, X);                         // uses current adjacency (without X‑Y)
    // add the new edge for future traversals
    adj[X].push_back(Y);
    adj[Y].push_back(X);
    // DSU union
    dsuPar[repY] = repX;
    dsuSize[repX] += dsuSize[repY];
}

/* ---------- Main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N >> Q) {
        maxVal = N;
        for (int i = 1; i <= N; ++i) {
            cin >> A[i];
            adj[i].clear();
            dsuPar[i] = i;
            dsuSize[i] = 1;
            depthArr[i] = 0;
            for (int j = 0; j < LOG; ++j) up[i][j] = 0;
        }
        segTot = 0;                         // node 0 is the null node (all zero)
        // initialise each singleton tree
        for (int i = 1; i <= N; ++i) {
            pstRoot[i] = pstUpdate(0, 1, maxVal, A[i]);
        }

        int d = 0;                          // last answer (for XOR)
        for (int qq = 0; qq < Q; ++qq) {
            int type; 
            cin >> type;
            if (type == 0) {
                int X, Y;
                cin >> X >> Y;
                X ^= d; Y ^= d;
                linkEdge(X, Y);
            } else { // type == 1
                int X, Y, K;
                cin >> X >> Y >> K;
                X ^= d; Y ^= d; K ^= d;
                int ans = 0;
                if (dsuFind(X) == dsuFind(Y)) {
                    int w = lca(X, Y);
                    int cntX = pstQuery(pstRoot[X], 1, maxVal, K);
                    int cntY = pstQuery(pstRoot[Y], 1, maxVal, K);
                    int cntW = pstQuery(pstRoot[w], 1, maxVal, K);
                    ans = cntX + cntY - 2 * cntW + (A[w] <= K ? 1 : 0);
                }
                cout << ans << '\n';
                d = ans;
            }
        }
    }
    return 0;
}
