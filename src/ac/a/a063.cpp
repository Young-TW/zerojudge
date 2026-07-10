#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <utility>
using namespace std;

struct Node {
    int val;
    uint32_t pri;
    int sz;
    bool rev;
    Node *l, *r;
    Node(int v, uint32_t p) : val(v), pri(p), sz(1), rev(false), l(nullptr), r(nullptr) {}
};

static inline int szOf(Node* t) { return t ? t->sz : 0; }

static inline void pushUp(Node* t) {
    if (t) t->sz = 1 + szOf(t->l) + szOf(t->r);
}

static inline void applyRev(Node* t) {
    if (!t) return;
    t->rev ^= true;
}

static inline void pushDown(Node* t) {
    if (t && t->rev) {
        t->rev = false;
        swap(t->l, t->r);
        if (t->l) applyRev(t->l);
        if (t->r) applyRev(t->r);
    }
}

// split by size: left gets first k, right gets rest
static void split(Node* t, int k, Node*& a, Node*& b) {
    if (!t) { a = b = nullptr; return; }
    pushDown(t);
    int ls = szOf(t->l);
    if (k <= ls) {
        b = t;
        split(t->l, k, a, b->l);
        pushUp(b);
    } else {
        a = t;
        split(t->r, k - ls - 1, a->r, b);
        pushUp(a);
    }
}

static Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->pri < b->pri) {
        pushDown(a);
        a->r = merge(a->r, b);
        pushUp(a);
        return a;
    } else {
        pushDown(b);
        b->l = merge(a, b->l);
        pushUp(b);
        return b;
    }
}

static mt19937 rng(987654321u);

static Node* build(int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = (lo + hi) >> 1;
    Node* t = new Node(mid, rng());
    t->l = build(lo, mid - 1);
    t->r = build(mid + 1, hi);
    pushUp(t);
    return t;
}

// output buffer
static void inorder(Node* t, vector<int>& out) {
    if (!t) return;
    pushDown(t);
    inorder(t->l, out);
    out.push_back(t->val);
    inorder(t->r, out);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    string outBuf;
    while (cin >> N >> M) {
        Node* root = build(1, N);
        for (int i = 0; i < M; i++) {
            int P, Q;
            cin >> P >> Q;
            Node *a, *b, *c, *d;
            // left part [1, P-1], middle [P, Q], right [Q+1, N]
            split(root, P - 1, a, b);   // a = [1,P-1], b = [P,N]
            split(b, Q - P + 1, c, d);  // c = [P,Q], d = [Q+1,N]
            applyRev(c);
            root = merge(a, merge(c, d));
        }
        vector<int> res;
        res.reserve(N);
        inorder(root, res);
        for (int i = 0; i < N; i++) {
            if (i) outBuf += ' ';
            outBuf += to_string(res[i]);
        }
        outBuf += '\n';
    }
    fwrite(outBuf.data(), 1, outBuf.size(), stdout);
    return 0;
}
