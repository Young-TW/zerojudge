// b405 【記憶中】之記憶中的序列 - self-written solution
// Fully persistent treap (rope) with lazy range-add + lazy reverse,
// supporting revert-to-any-past-version (op 0). Range max/min/sum queries.
// Queries are answered WITHOUT allocating nodes (non-mutating descent),
// so only structural modifications consume memory.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    int l, r;
    int sz;
    unsigned pri;
    ll val, sum, mx, mn, add;
    bool rev;
};

static const int CAP = 8000000;   // demand-zero BSS: RSS only for touched nodes
static Node pool[CAP];
static int top = 0;               // node 0 = null sentinel

static mt19937 rng(20250726u);

inline int new_node(ll v) {
    int u = ++top;
    Node &p = pool[u];
    p.l = p.r = 0;
    p.sz = 1;
    p.pri = rng();
    p.val = p.sum = p.mx = p.mn = v;
    p.add = 0;
    p.rev = false;
    return u;
}
inline int clone(int u) {
    int v = ++top;
    pool[v] = pool[u];
    return v;
}
inline void pushup(int u) {
    int L = pool[u].l, R = pool[u].r;
    pool[u].sz = 1 + pool[L].sz + pool[R].sz;
    pool[u].sum = pool[u].val + pool[L].sum + pool[R].sum;
    pool[u].mx = max(pool[u].val, max(pool[L].mx, pool[R].mx));
    pool[u].mn = min(pool[u].val, min(pool[L].mn, pool[R].mn));
}
inline void apply_add_inplace(int c, ll v) {
    pool[c].val += v;
    pool[c].sum += v * pool[c].sz;
    pool[c].mx += v;
    pool[c].mn += v;
    pool[c].add += v;
}
inline void pushdown(int u) {          // u must be an owned (cloned) node
    ll ad = pool[u].add;
    bool rv = pool[u].rev;
    if (ad == 0 && !rv) return;
    if (pool[u].l) {
        int c = clone(pool[u].l);
        if (ad) apply_add_inplace(c, ad);
        if (rv) pool[c].rev ^= 1;
        pool[u].l = c;
    }
    if (pool[u].r) {
        int c = clone(pool[u].r);
        if (ad) apply_add_inplace(c, ad);
        if (rv) pool[c].rev ^= 1;
        pool[u].r = c;
    }
    if (rv) swap(pool[u].l, pool[u].r);
    pool[u].add = 0;
    pool[u].rev = false;
}

// split first k elements into a, the rest into b (persistent: clones the path)
void split(int u, int k, int &a, int &b) {
    if (u == 0) { a = b = 0; return; }
    u = clone(u);
    pushdown(u);
    int L = pool[u].l;
    if (pool[L].sz >= k) {
        int a2, b2;
        split(L, k, a2, b2);
        pool[u].l = b2;
        pushup(u);
        a = a2; b = u;
    } else {
        int a2, b2;
        split(pool[u].r, k - pool[L].sz - 1, a2, b2);
        pool[u].r = a2;
        pushup(u);
        a = u; b = b2;
    }
}
int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    if (pool[a].pri > pool[b].pri) {
        a = clone(a);
        pushdown(a);
        pool[a].r = merge(pool[a].r, b);
        pushup(a);
        return a;
    } else {
        b = clone(b);
        pushdown(b);
        pool[b].l = merge(a, pool[b].l);
        pushup(b);
        return b;
    }
}

// ---- non-mutating range query over visible positions [ql,qr] (1-indexed) ----
struct Agg { ll sum, mx, mn; };
static const Agg NEUT = {0, LLONG_MIN, LLONG_MAX};
inline Agg comb(const Agg &a, const Agg &b) {
    return { a.sum + b.sum, max(a.mx, b.mx), min(a.mn, b.mn) };
}
// flip = pending reversal inherited from ancestors; eadd = pending add inherited.
Agg query(int u, bool flip, ll eadd, int ql, int qr) {
    if (u == 0 || ql > qr) return NEUT;
    int total = pool[u].sz;
    if (ql <= 1 && qr >= total) {
        return { pool[u].sum + eadd * (ll)total, pool[u].mx + eadd, pool[u].mn + eadd };
    }
    bool g = flip ^ pool[u].rev;
    ll ca = eadd + pool[u].add;
    int lc = g ? pool[u].r : pool[u].l;
    int rc = g ? pool[u].l : pool[u].r;
    int s1 = pool[lc].sz;
    Agg res = NEUT;
    if (ql <= s1) {
        res = comb(res, query(lc, g, ca, max(ql, 1), min(qr, s1)));
    }
    int np = s1 + 1;
    if (ql <= np && qr >= np) {
        ll v = pool[u].val + eadd;
        res = comb(res, Agg{v, v, v});
    }
    if (qr >= s1 + 2) {
        res = comb(res, query(rc, g, ca, max(ql, s1 + 2) - np, qr - np));
    }
    return res;
}

// ---- O(n) build of a balanced treap (Cartesian tree by priority) ----
void pushup_all(int u) {
    if (!u) return;
    pushup_all(pool[u].l);
    pushup_all(pool[u].r);
    pushup(u);
}
int build(const vector<ll> &a) {
    int n = a.size();
    if (n == 0) return 0;
    vector<int> stk;
    stk.reserve(n);
    for (int i = 0; i < n; ++i) {
        int cur = new_node(a[i]);
        int last = 0;
        while (!stk.empty() && pool[stk.back()].pri < pool[cur].pri) {
            last = stk.back();
            stk.pop_back();
        }
        pool[cur].l = last;
        if (!stk.empty()) pool[stk.back()].r = cur;
        stk.push_back(cur);
    }
    int root = stk.front();
    pushup_all(root);
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // null sentinel (index 0): identity for aggregates
    pool[0].l = pool[0].r = 0;
    pool[0].sz = 0;
    pool[0].pri = 0;
    pool[0].val = 0;
    pool[0].sum = 0;
    pool[0].mx = LLONG_MIN;
    pool[0].mn = LLONG_MAX;
    pool[0].add = 0;
    pool[0].rev = false;

    int n;
    while (cin >> n) {
        top = 0;
        vector<ll> init(n);
        for (int i = 0; i < n; ++i) cin >> init[i];
        int root0 = build(init);

        int q;
        cin >> q;
        vector<int> ver(q + 1);
        ver[0] = root0;

        ll ans = 0;   // last query answer (xor key), full 64-bit
        for (int d = 1; d <= q; ++d) {
            ll rt;
            cin >> rt;
            int t = (int)(rt ^ ans);
            int cur = ver[d - 1];
            int nxt = cur;

            if (t == 0) {
                ll rk; cin >> rk;
                int k = (int)(rk ^ ans);
                nxt = ver[k];
            } else if (t == 1) {
                ll rx, rv; cin >> rx >> rv;
                int x = (int)(rx ^ ans);
                ll v = rv ^ ans;
                int L, R;
                split(cur, x, L, R);
                nxt = merge(merge(L, new_node(v)), R);
            } else if (t == 2) {
                ll rx; cin >> rx;
                int x = (int)(rx ^ ans);
                int L, mid, R;
                split(cur, x - 1, L, mid);
                split(mid, 1, mid, R);
                nxt = merge(L, R);
            } else if (t == 3) {
                ll rx, ry; cin >> rx >> ry;
                int x = (int)(rx ^ ans), y = (int)(ry ^ ans);
                if (x > y) swap(x, y);
                int L, mid, R;
                split(cur, x - 1, L, mid);
                split(mid, y - x + 1, mid, R);
                pool[mid].rev ^= 1;
                nxt = merge(merge(L, mid), R);
            } else if (t == 4) {
                ll rx, ry, rv; cin >> rx >> ry >> rv;
                int x = (int)(rx ^ ans), y = (int)(ry ^ ans);
                ll v = rv ^ ans;
                if (x > y) swap(x, y);
                int L, mid, R;
                split(cur, x - 1, L, mid);
                split(mid, y - x + 1, mid, R);
                apply_add_inplace(mid, v);
                nxt = merge(merge(L, mid), R);
            } else { // 5,6,7 queries -- non-allocating
                ll rx, ry; cin >> rx >> ry;
                int x = (int)(rx ^ ans), y = (int)(ry ^ ans);
                if (x > y) swap(x, y);
                Agg a = query(cur, false, 0, x, y);
                ll out;
                if (t == 5) out = a.mx;
                else if (t == 6) out = a.mn;
                else out = a.sum;
                cout << out << '\n';
                ans = out;
            }
            ver[d] = nxt;
        }
    }
    return 0;
}
