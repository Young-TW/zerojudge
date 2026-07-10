#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

typedef long long ll;

struct Node {
    ll key;
    unsigned pri;
    int size;
    Node *l, *r;
};

static unsigned rngState = 2463534242u;
static inline unsigned rng() {
    rngState ^= rngState << 13;
    rngState ^= rngState >> 17;
    rngState ^= rngState << 5;
    return rngState;
}

static inline int sz(Node* t) { return t ? t->size : 0; }
static inline void pull(Node* t) { t->size = 1 + sz(t->l) + sz(t->r); }

// split: a gets keys < key, b gets keys >= key
static void split(Node* t, ll key, Node*& a, Node*& b) {
    if (!t) { a = b = nullptr; return; }
    if (t->key < key) {
        a = t;
        split(t->r, key, t->r, b);
    } else {
        b = t;
        split(t->l, key, a, t->l);
    }
    pull(t);
}

static Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->pri > b->pri) {
        a->r = merge(a->r, b);
        pull(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

int main() {
    int n;
    ll minSal;
    while (scanf("%d %lld", &n, &minSal) == 2) {
        Node* pool = new Node[n + 1];
        int poolIdx = 0;
        Node* root = nullptr;
        ll delta = 0;
        ll departed = 0;
        string out;

        for (int i = 0; i < n; i++) {
            char cmd;
            ll k;
            if (scanf(" %c %lld", &cmd, &k) != 2) break;

            if (cmd == 'I') {
                if (k < minSal) continue; // never joins, not counted
                Node* nd = &pool[poolIdx++];
                nd->key = k - delta;
                nd->pri = rng();
                nd->size = 1;
                nd->l = nd->r = nullptr;
                Node *a, *b;
                split(root, k - delta, a, b);
                root = merge(merge(a, nd), b);
            } else if (cmd == 'A') {
                delta += k;
            } else if (cmd == 'S') {
                delta -= k;
                ll thr = minSal - delta; // remove stored < thr
                Node *a, *b;
                split(root, thr, a, b);
                departed += sz(a);
                root = b;
            } else if (cmd == 'F') {
                if (k < 1 || k > (ll)sz(root)) {
                    out += "-1\n";
                } else {
                    Node* t = root;
                    ll kk = k;
                    ll val = 0;
                    while (t) {
                        int rs = sz(t->r);
                        if (kk <= rs) {
                            t = t->r;
                        } else if (kk == rs + 1) {
                            val = t->key;
                            break;
                        } else {
                            kk -= rs + 1;
                            t = t->l;
                        }
                    }
                    out += to_string(val + delta);
                    out += '\n';
                }
            }
        }
        out += to_string(departed);
        out += '\n';
        fputs(out.c_str(), stdout);
        delete[] pool;
    }
    return 0;
}
