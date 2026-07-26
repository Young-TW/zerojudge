#include <bits/stdc++.h>
using namespace std;

struct Treap {
    int val;          // stored value (invaders for entry, 0 for exit)
    int sum;          // sum of subtree
    int sz;           // size of subtree
    unsigned pri;     // heap priority
    Treap *l, *r, *p; // children and parent
    Treap(int v = 0, unsigned pr = 0) : val(v), sum(v), sz(1),
        pri(pr), l(nullptr), r(nullptr), p(nullptr) {}
};

inline int getSize(Treap *t) { return t ? t->sz : 0; }
inline int getSum (Treap *t) { return t ? t->sum : 0; }

void upd(Treap *t) {
    if (!t) return;
    t->sz = 1 + getSize(t->l) + getSize(t->r);
    t->sum = t->val + getSum(t->l) + getSum(t->r);
    if (t->l) t->l->p = t;
    if (t->r) t->r->p = t;
}

/* merge two treaps: all nodes of a come before nodes of b */
Treap* merge(Treap *a, Treap *b) {
    if (!a) { if (b) b->p = nullptr; return b; }
    if (!b) { a->p = nullptr; return a; }
    if (a->pri < b->pri) {
        a->r = merge(a->r, b);
        if (a->r) a->r->p = a;
        upd(a);
        a->p = nullptr;
        return a;
    } else {
        b->l = merge(a, b->l);
        if (b->l) b->l->p = b;
        upd(b);
        b->p = nullptr;
        return b;
    }
}

/* split first k nodes to left, rest to right (k may be 0) */
pair<Treap*,Treap*> split(Treap *t, int k) {
    if (!t) return {nullptr, nullptr};
    if (getSize(t->l) >= k) {
        auto leftSplit = split(t->l, k);
        t->l = leftSplit.second;
        if (t->l) t->l->p = t;
        upd(t);
        if (leftSplit.first) leftSplit.first->p = nullptr;
        t->p = nullptr;
        return {leftSplit.first, t};
    } else {
        int nk = k - getSize(t->l) - 1;
        auto rightSplit = split(t->r, nk);
        t->r = rightSplit.first;
        if (t->r) t->r->p = t;
        upd(t);
        if (rightSplit.second) rightSplit.second->p = nullptr;
        t->p = nullptr;
        return {t, rightSplit.second};
    }
}

/* root of the whole treap containing node x */
Treap* getRoot(Treap *x) {
    while (x && x->p) x = x->p;
    return x;
}

/* 1‑based index of node x inside its treap */
int getIndex(Treap *x) {
    int idx = getSize(x->l) + 1;
    while (x->p) {
        if (x == x->p->r) {
            idx += getSize(x->p->l) + 1;
        }
        x = x->p;
    }
    return idx;
}

/* random generator for priorities */
static std::mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<Treap*> ent(N + 1), ext(N + 1);
        vector<int> parent(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int w; cin >> w;
            ent[i] = new Treap(w, rng());
            ext[i] = new Treap(0, rng());
            Treap* t = merge(ent[i], ext[i]); // initial isolated tree
            (void)t; // root not needed now
        }

        for (int i = 0; i < M; ++i) {
            int op; cin >> op;
            if (op == 1) {                 // link u under v
                int u, v; cin >> u >> v;
                Treap* ru = getRoot(ent[u]);
                Treap* rv = getRoot(ent[v]);
                int pos = getIndex(ent[v]);          // position of enter(v)
                auto sp1 = split(rv, pos);            // left includes enter(v)
                Treap* left = sp1.first;
                Treap* right = sp1.second;
                Treap* merged = merge(left, ru);
                Treap* newRoot = merge(merged, right);
                (void)newRoot;
                parent[u] = v;
            } else if (op == 2) {          // cut u from its parent
                int u; cin >> u;
                Treap* root = getRoot(ent[u]);
                int l = getIndex(ent[u]);
                int r = getIndex(ext[u]);
                if (l > r) swap(l, r);
                auto s1 = split(root, l - 1);
                auto s2 = split(s1.second, r - l + 1);
                Treap* A = s1.first;
                Treap* C = s2.first;   // subtree of u
                Treap* D = s2.second;
                Treap* newRoot = merge(A, D); // remaining tree
                (void)newRoot;
                // C stays as a separate treap (the new isolated tree)
                parent[u] = 0;
            } else if (op == 3) {          // point update
                int u, w; cin >> u >> w;
                ent[u]->val = w;
                Treap* cur = ent[u];
                while (cur) {
                    upd(cur);
                    cur = cur->p;
                }
            } else if (op == 4) {          // subtree sum query
                int u; cin >> u;
                Treap* root = getRoot(ent[u]);
                int l = getIndex(ent[u]);
                int r = getIndex(ext[u]);
                if (l > r) swap(l, r);
                auto s1 = split(root, l - 1);
                auto s2 = split(s1.second, r - l + 1);
                int ans = getSum(s2.first);
                Treap* tmp = merge(s2.first, s2.second);
                Treap* newRoot = merge(s1.first, tmp);
                (void)newRoot;
                cout << ans << '\n';
            }
        }
        // clean up (optional, program ends soon)
    }
    return 0;
}
