#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

struct Node {
    int ch[2];          // left, right child in splay
    int fa;             // parent (splay parent or tree parent)
    long long val;      // own value
    long long sum;      // aggregate of whole represented subtree
    long long vsum;     // sum of virtual children
    bool rev;           // lazy reversal flag
    Node() : ch{0,0}, fa(0), val(0), sum(0), vsum(0), rev(false) {}
} tr[MAXN];

inline bool isRoot(int x) {
    int f = tr[x].fa;
    if (!f) return true;
    return (tr[f].ch[0] != x && tr[f].ch[1] != x);
}

inline void push_up(int x) {
    tr[x].sum = tr[x].val + tr[tr[x].ch[0]].sum + tr[tr[x].ch[1]].sum + tr[x].vsum;
}

inline void push_rev(int x) {
    if (!x) return;
    tr[x].rev ^= 1;
    swap(tr[x].ch[0], tr[x].ch[1]);
}

inline void push_down(int x) {
    if (tr[x].rev) {
        if (tr[x].ch[0]) push_rev(tr[x].ch[0]);
        if (tr[x].ch[1]) push_rev(tr[x].ch[1]);
        tr[x].rev = false;
    }
}

void rotate(int x) {
    int y = tr[x].fa;
    int z = tr[y].fa;
    int dir = (tr[y].ch[1] == x);
    int w = tr[x].ch[dir ^ 1];

    if (!isRoot(y)) {
        if (tr[z].ch[0] == y) tr[z].ch[0] = x;
        else if (tr[z].ch[1] == y) tr[z].ch[1] = x;
    }
    tr[x].fa = z;

    tr[x].ch[dir ^ 1] = y;
    tr[y].fa = x;

    tr[y].ch[dir] = w;
    if (w) tr[w].fa = y;

    push_up(y);
    push_up(x);
}

void splay(int x) {
    static int stk[MAXN];
    int top = 0;
    int y = x;
    stk[++top] = y;
    while (!isRoot(y)) {
        y = tr[y].fa;
        stk[++top] = y;
    }
    while (top) push_down(stk[top--]);

    while (!isRoot(x)) {
        int y = tr[x].fa;
        int z = tr[y].fa;
        if (!isRoot(y)) {
            if ((tr[y].ch[0] == x) ^ (tr[z].ch[0] == y))
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}

/* expose path from root to x, making x the rightmost node of the preferred path */
void access(int x) {
    int last = 0;
    for (int y = x; y; y = tr[y].fa) {
        splay(y);
        // old right child becomes virtual
        if (tr[y].ch[1]) tr[y].vsum += tr[tr[y].ch[1]].sum;
        // the part already processed (last) becomes preferred, remove from virtual
        if (last) tr[y].vsum -= tr[last].sum;
        tr[y].ch[1] = last;
        push_up(y);
        last = y;
    }
    splay(x);
}

/* make x the root of its represented tree */
void makeRoot(int x) {
    access(x);
    splay(x);
    push_rev(x);
}

/* return the root of the tree containing x */
int findRoot(int x) {
    access(x);
    splay(x);
    while (true) {
        push_down(x);
        if (!tr[x].ch[0]) break;
        x = tr[x].ch[0];
    }
    splay(x);
    return x;
}

/* link two different trees by edge u‑v (u becomes child of v) */
void link(int u, int v) {
    makeRoot(u);
    if (findRoot(v) == u) return;          // already connected, should not happen
    access(v);
    splay(v);
    tr[v].vsum += tr[u].sum;
    push_up(v);
    tr[u].fa = v;
}

/* cut the edge u‑v (it exists) */
void cut(int u, int v) {
    makeRoot(u);
    if (findRoot(v) != u) return;          // not connected, should not happen
    access(v);
    splay(v);
    if (tr[v].ch[0] == u) {
        tr[v].ch[0] = 0;
        tr[u].fa = 0;
        push_up(v);
    }
}

/* set value of vertex u to w */
void setValue(int u, long long w) {
    access(u);
    splay(u);
    tr[u].val = w;
    push_up(u);
}

/* query sum of the whole component containing u */
long long querySum(int u) {
    makeRoot(u);
    access(u);
    splay(u);
    return tr[u].sum;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N; ++i) {
            long long x; cin >> x;
            tr[i] = Node();
            tr[i].val = tr[i].sum = x;
        }
        for (int i = 0; i < M; ++i) {
            int op; cin >> op;
            if (op == 1) {          // open (link)
                int u, v; cin >> u >> v;
                link(u, v);
            } else if (op == 2) {   // close (cut)
                int u, v; cin >> u >> v;
                cut(u, v);
            } else if (op == 3) {   // modify value
                int u; long long w; cin >> u >> w;
                setValue(u, w);
            } else if (op == 4) {   // query
                int u; cin >> u;
                cout << querySum(u) << '\n';
            }
        }
    }
    return 0;
}
