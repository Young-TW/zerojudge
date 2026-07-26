#include <bits/stdc++.h>
using namespace std;

const long long NEG_INF = -4e18;          // sufficiently small

struct Node {
    int val;                 // value of this element
    int sz;                  // size of subtree
    long long sum;           // sum of subtree
    long long pre;           // maximum prefix sum
    long long suf;           // maximum suffix sum
    long long mx;            // maximum sub‑array sum
    bool rev;                // lazy reverse flag
    bool same;               // lazy "make same" flag
    int same_val;            // value for "make same"
    unsigned pri;            // heap priority
    Node *l, *r;
    Node(int v, unsigned p) : val(v), sz(1), sum(v), pre(v), suf(v), mx(v),
                              rev(false), same(false), same_val(0),
                              pri(p), l(nullptr), r(nullptr) {}
};

mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

inline int getSize(Node *o) { return o ? o->sz : 0; }
inline long long getSum(Node *o) { return o ? o->sum : 0; }
inline long long getPre(Node *o) { return o ? o->pre : NEG_INF; }
inline long long getSuf(Node *o) { return o ? o->suf : NEG_INF; }
inline long long getMx(Node *o)  { return o ? o->mx  : NEG_INF; }

/* ---------- lazy propagation ---------- */
void applySame(Node *o, int c) {
    if (!o) return;
    o->same = true;
    o->same_val = c;
    o->rev = false;
    o->val = c;
    o->sum = 1LL * c * o->sz;
    if (c >= 0) {
        o->pre = o->suf = o->mx = o->sum;
    } else {
        o->pre = o->suf = o->mx = c;
    }
}

void applyRev(Node *o) {
    if (!o) return;
    o->rev ^= 1;
    swap(o->l, o->r);
    swap(o->pre, o->suf);
}

/* push lazy tags to children */
void pushDown(Node *o) {
    if (!o) return;
    if (o->same) {
        applySame(o->l, o->same_val);
        applySame(o->r, o->same_val);
        o->same = false;
    }
    if (o->rev) {
        applyRev(o->l);
        applyRev(o->r);
        o->rev = false;
    }
}

/* recalculate information from children */
void pull(Node *o) {
    if (!o) return;
    o->sz = 1 + getSize(o->l) + getSize(o->r);
    o->sum = o->val + getSum(o->l) + getSum(o->r);

    long long lsum = getSum(o->l);
    long long rsum = getSum(o->r);

    long long lpre = getPre(o->l);
    long long rpre = getPre(o->r);
    long long lsuf = getSuf(o->l);
    long long rsuf = getSuf(o->r);
    long long lmx  = getMx(o->l);
    long long rmx  = getMx(o->r);

    // prefix
    o->pre = max(lpre, lsum + o->val);
    o->pre = max(o->pre, lsum + o->val + rpre);

    // suffix
    o->suf = max(rsuf, rsum + o->val);
    o->suf = max(o->suf, rsum + o->val + lsuf);

    // max sub‑array
    o->mx = max({lmx, rmx, (long long)o->val,
                 lsuf + o->val,
                 o->val + rpre,
                 lsuf + o->val + rpre});
}

/* ---------- split / merge ---------- */
// split by size: left contains first k elements
void split(Node *root, int k, Node *&left, Node *&right) {
    if (!root) { left = right = nullptr; return; }
    pushDown(root);
    if (getSize(root->l) >= k) {
        split(root->l, k, left, root->l);
        right = root;
        pull(right);
    } else {
        split(root->r, k - getSize(root->l) - 1, root->r, right);
        left = root;
        pull(left);
    }
}

// merge two trees, all keys in L are before those in R
Node* merge(Node *L, Node *R) {
    if (!L) return R;
    if (!R) return L;
    if (L->pri > R->pri) {
        pushDown(L);
        L->r = merge(L->r, R);
        pull(L);
        return L;
    } else {
        pushDown(R);
        R->l = merge(L, R->l);
        pull(R);
        return R;
    }
}

/* ---------- utility ---------- */
void deleteTree(Node *o) {
    if (!o) return;
    deleteTree(o->l);
    deleteTree(o->r);
    delete o;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        Node *root = nullptr;
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            root = merge(root, new Node(x, rng()));
        }
        for (int i = 0; i < M; ++i) {
            string cmd; cin >> cmd;
            if (cmd == "INSERT") {
                int pos, tot; cin >> pos >> tot;
                Node *mid = nullptr;
                for (int j = 0; j < tot; ++j) {
                    int v; cin >> v;
                    mid = merge(mid, new Node(v, rng()));
                }
                Node *L, *R;
                split(root, pos, L, R);          // after pos elements
                root = merge(merge(L, mid), R);
            }
            else if (cmd == "DELETE") {
                int pos, tot; cin >> pos >> tot;
                Node *L, *M1, *R;
                split(root, pos - 1, L, M1);
                split(M1, tot, M1, R);
                deleteTree(M1);
                root = merge(L, R);
            }
            else if (cmd == "MAKE-SAME") {
                int pos, tot, c; cin >> pos >> tot >> c;
                Node *L, *M1, *R;
                split(root, pos - 1, L, M1);
                split(M1, tot, M1, R);
                applySame(M1, c);
                root = merge(L, merge(M1, R));
            }
            else if (cmd == "REVERSE") {
                int pos, tot; cin >> pos >> tot;
                Node *L, *M1, *R;
                split(root, pos - 1, L, M1);
                split(M1, tot, M1, R);
                applyRev(M1);
                root = merge(L, merge(M1, R));
            }
            else if (cmd == "GET-SUM") {
                int pos, tot; cin >> pos >> tot;
                Node *L, *M1, *R;
                split(root, pos - 1, L, M1);
                split(M1, tot, M1, R);
                cout << (M1 ? M1->sum : 0LL) << '\n';
                root = merge(L, merge(M1, R));
            }
            else if (cmd == "MAX-SUM") {
                if (root)
                    cout << root->mx << '\n';
                else
                    cout << 0 << '\n';
            }
        }
        deleteTree(root);
    }
    return 0;
}
