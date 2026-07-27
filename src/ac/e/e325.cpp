#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int rand_pri() {
    return rand();
}

struct Node {
    long long start;
    int len, step;
    int pri;
    Node *lc, *rc;
    int sz;
    Node(long long s, int l, int st) : start(s), len(l), step(st), pri(rand_pri()), lc(nullptr), rc(nullptr), sz(l) {}
};

int get_sz(Node* t) { return t ? t->sz : 0; }
void upd_sz(Node* t) {
    if (t) t->sz = t->len + get_sz(t->lc) + get_sz(t->rc);
}

Node* merge(Node* a, Node* b);

void split(Node* t, int k, Node* &L, Node* &R) {
    if (!t) { L = R = nullptr; return; }
    int left_sz = get_sz(t->lc);
    if (k <= left_sz) {
        split(t->lc, k, L, t->lc);
        R = t;
    } else if (k >= left_sz + t->len) {
        split(t->rc, k - left_sz - t->len, t->rc, R);
        L = t;
    } else {
        int left_len = k - left_sz;
        int right_len = t->len - left_len;
        Node* left_node = new Node(t->start, left_len, t->step);
        Node* right_node = new Node(t->start + (long long)left_len * t->step, right_len, t->step);
        L = merge(t->lc, left_node);
        R = merge(right_node, t->rc);
        delete t;
        return;
    }
    upd_sz(t);
}

Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pri > b->pri) {
        a->rc = merge(a->rc, b);
        upd_sz(a);
        return a;
    } else {
        b->lc = merge(a, b->lc);
        upd_sz(b);
        return b;
    }
}

void delete_tree(Node* t) {
    if (!t) return;
    delete_tree(t->lc);
    delete_tree(t->rc);
    delete t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n, m, q;
    while (cin >> n >> m >> q) {
        vector<Node*> row_root(n+1, nullptr);
        for (int i = 1; i <= n; ++i) {
            if (m > 1) {
                long long start = (long long)(i-1) * m + 1;
                row_root[i] = new Node(start, m-1, 1);
            }
        }
        Node* last_root = nullptr;
        if (n > 0) {
            last_root = new Node(m, n, m);
        }
        for (int i = 0; i < q; ++i) {
            int x, y;
            cin >> x >> y;
            if (y == m) {
                Node *L, *mid, *R;
                split(last_root, x-1, L, R);
                split(R, 1, mid, R);
                long long ans = mid->start;
                cout << ans << '\n';
                last_root = merge(merge(L, R), mid);
            } else {
                Node *Lx, *midx, *Rx;
                split(row_root[x], y-1, Lx, Rx);
                split(Rx, 1, midx, Rx);
                long long ans = midx->start;
                cout << ans << '\n';
                Node *Llast, *midlast, *Rlast;
                split(last_root, x-1, Llast, Rlast);
                split(Rlast, 1, midlast, Rlast);
                row_root[x] = merge(merge(Lx, Rx), midlast);
                last_root = merge(merge(Llast, Rlast), midx);
            }
        }
        for (int i = 1; i <= n; ++i) {
            delete_tree(row_root[i]);
        }
        delete_tree(last_root);
    }
    return 0;
}
