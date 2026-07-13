#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <string>
#include <utility>

using namespace std;

const long long NEG_INF = -4000000000000000000LL;

struct Node {
    int val, sz, pri;
    long long sum, pre_max, suf_max, max_sum;
    bool rev, same;
    int same_val;
    Node *l, *r;
    Node(int v, int p) : val(v), sz(1), pri(p), sum(v), pre_max(v), suf_max(v), max_sum(v),
                         rev(false), same(false), same_val(0), l(nullptr), r(nullptr) {}
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int get_size(Node* o) { return o ? o->sz : 0; }
inline long long get_sum(Node* o) { return o ? o->sum : 0; }
inline long long get_pre_max(Node* o) { return o ? o->pre_max : NEG_INF; }
inline long long get_suf_max(Node* o) { return o ? o->suf_max : NEG_INF; }
inline long long get_max_sum(Node* o) { return o ? o->max_sum : NEG_INF; }

void apply_same(Node* o, int c) {
    if (!o) return;
    o->same = true;
    o->same_val = c;
    o->rev = false;
    o->val = c;
    o->sum = (long long)c * o->sz;
    if (c >= 0) {
        o->pre_max = o->suf_max = o->max_sum = o->sum;
    } else {
        o->pre_max = o->suf_max = o->max_sum = c;
    }
}

void apply_rev(Node* o) {
    if (!o) return;
    o->rev ^= 1;
    swap(o->l, o->r);
    swap(o->pre_max, o->suf_max);
}

void push_down(Node* o) {
    if (!o) return;
    if (o->same) {
        apply_same(o->l, o->same_val);
        apply_same(o->r, o->same_val);
        o->same = false;
    }
    if (o->rev) {
        apply_rev(o->l);
        apply_rev(o->r);
        o->rev = false;
    }
}

void update(Node* o) {
    if (!o) return;
    o->sz = 1 + get_size(o->l) + get_size(o->r);
    o->sum = o->val + get_sum(o->l) + get_sum(o->r);
    long long l_pre = get_pre_max(o->l);
    long long l_sum = get_sum(o->l);
    long long r_pre = get_pre_max(o->r);
    long long r_sum = get_sum(o->r);
    long long l_suf = get_suf_max(o->l);
    long long r_suf = get_suf_max(o->r);
    long long l_max = get_max_sum(o->l);
    long long r_max = get_max_sum(o->r);

    o->pre_max = max(l_pre, l_sum + o->val);
    o->pre_max = max(o->pre_max, l_sum + o->val + r_pre);

    o->suf_max = max(r_suf, r_sum + o->val);
    o->suf_max = max(o->suf_max, r_sum + o->val + l_suf);

    o->max_sum = max({l_max, r_max, (long long)o->val,
                      l_suf + o->val, o->val + r_pre, l_suf + o->val + r_pre});
}

void split(Node* o, int k, Node*& l, Node*& r) {
    if (!o) { l = r = nullptr; return; }
    push_down(o);
    if (get_size(o->l) >= k) {
        split(o->l, k, l, o->l);
        r = o;
        update(r);
    } else {
        split(o->r, k - get_size(o->l) - 1, o->r, r);
        l = o;
        update(l);
    }
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->pri > r->pri) {
        push_down(l);
        l->r = merge(l->r, r);
        update(l);
        return l;
    } else {
        push_down(r);
        r->l = merge(l, r->l);
        update(r);
        return r;
    }
}

void delete_tree(Node* o) {
    if (!o) return;
    delete_tree(o->l);
    delete_tree(o->r);
    delete o;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        Node* root = nullptr;
        for (int i = 0; i < N; i++) {
            int x; cin >> x;
            root = merge(root, new Node(x, rng()));
        }
        for (int i = 0; i < M; i++) {
            string cmd; cin >> cmd;
            if (cmd == "INSERT") {
                int pos, tot; cin >> pos >> tot;
                Node* mid = nullptr;
                for (int j = 0; j < tot; j++) {
                    int c; cin >> c;
                    mid = merge(mid, new Node(c, rng()));
                }
                Node *left, *right;
                split(root, pos, left, right);
                root = merge(merge(left, mid), right);
            } else if (cmd == "DELETE") {
                int pos, tot; cin >> pos >> tot;
                Node *left, *mid, *right;
                split(root, pos - 1, left, mid);
                split(mid, tot, mid, right);
                delete_tree(mid);
                root = merge(left, right);
            } else if (cmd == "MAKE-SAME") {
                int pos, tot, c; cin >> pos >> tot >> c;
                Node *left, *mid, *right;
                split(root, pos - 1, left, mid);
                split(mid, tot, mid, right);
                apply_same(mid, c);
                root = merge(left, merge(mid, right));
            } else if (cmd == "REVERSE") {
                int pos, tot; cin >> pos >> tot;
                Node *left, *mid, *right;
                split(root, pos - 1, left, mid);
                split(mid, tot, mid, right);
                apply_rev(mid);
                root = merge(left, merge(mid, right));
            } else if (cmd == "GET-SUM") {
                int pos, tot; cin >> pos >> tot;
                Node *left, *mid, *right;
                split(root, pos - 1, left, mid);
                split(mid, tot, mid, right);
                cout << mid->sum << '\n';
                root = merge(left, merge(mid, right));
            } else if (cmd == "MAX-SUM") {
                cout << root->max_sum << '\n';
            }
        }
        delete_tree(root);
    }
    return 0;
}
