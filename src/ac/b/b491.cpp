#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <chrono>

using namespace std;

struct Node {
    int start_val; // document number at the first position of this interval
    int step;      // +1 or -1
    int len;       // length of this interval
    int sz;        // total length of subtree
    uint32_t pri;  // priority
    Node *l, *r, *p;
    bool rev;      // lazy reversal flag

    Node(int sv, int st, int ln, uint32_t pr)
        : start_val(sv), step(st), len(ln), sz(ln), pri(pr),
          l(nullptr), r(nullptr), p(nullptr), rev(false) {}
};

using pNode = Node*;

map<int, pNode> docMap; // key: minimum document number in the interval

// Fast RNG
static uint32_t rng_seed = chrono::steady_clock::now().time_since_epoch().count();
inline uint32_t rand_pri() {
    rng_seed = rng_seed * 1664525u + 1013904223u;
    return rng_seed;
}

inline void update(pNode t) {
    if (!t) return;
    t->sz = t->len;
    if (t->l) t->sz += t->l->sz;
    if (t->r) t->sz += t->r->sz;
}

inline void push(pNode t) {
    if (t && t->rev) {
        t->rev = false;
        swap(t->l, t->r);
        if (t->l) t->l->p = t;
        if (t->r) t->r->p = t;
        // reverse this interval
        t->start_val = t->start_val + t->step * (t->len - 1);
        t->step = -t->step;
        if (t->l) t->l->rev ^= true;
        if (t->r) t->r->rev ^= true;
    }
}

pNode merge(pNode l, pNode r) {
    if (!l) { if (r) r->p = nullptr; return r; }
    if (!r) { l->p = nullptr; return l; }
    if (l->pri > r->pri) {
        push(l);
        l->r = merge(l->r, r);
        if (l->r) l->r->p = l;
        update(l);
        l->p = nullptr;
        return l;
    } else {
        push(r);
        r->l = merge(l, r->l);
        if (r->l) r->l->p = r;
        update(r);
        r->p = nullptr;
        return r;
    }
}

void split(pNode t, int k, pNode& l, pNode& r) {
    if (!t) { l = r = nullptr; return; }
    push(t);
    int left_sz = t->l ? t->l->sz : 0;
    if (k < left_sz) {
        split(t->l, k, l, t->l);
        if (t->l) t->l->p = t;
        r = t;
        r->p = nullptr;
        update(r);
    } else if (k > left_sz + t->len) {
        split(t->r, k - left_sz - t->len, t->r, r);
        if (t->r) t->r->p = t;
        l = t;
        l->p = nullptr;
        update(l);
    } else {
        int offset = k - left_sz; // 0 <= offset <= t->len
        if (offset == 0) {
            l = t->l;
            if (l) l->p = nullptr;
            t->l = nullptr;
            r = t;
            r->p = nullptr;
            update(r);
        } else if (offset == t->len) {
            r = t->r;
            if (r) r->p = nullptr;
            t->r = nullptr;
            l = t;
            l->p = nullptr;
            update(l);
        } else {
            // split inside this node
            int old_len = t->len;
            int old_start = t->start_val;
            int old_step = t->step;
            int old_min = min(old_start, old_start + old_step * (old_len - 1));

            // create right part
            pNode right_node = new Node(old_start + old_step * offset, old_step, old_len - offset, rand_pri());
            right_node->rev = false;

            // modify t to be left part
            t->len = offset;
            pNode old_r = t->r;
            t->r = nullptr;
            update(t);

            // update docMap for t
            int new_min_t = min(t->start_val, t->start_val + t->step * (t->len - 1));
            docMap.erase(old_min);
            docMap[new_min_t] = t;

            // update docMap for right_node
            int new_min_r = min(right_node->start_val, right_node->start_val + right_node->step * (right_node->len - 1));
            docMap[new_min_r] = right_node;

            // merge right_node with old_r
            r = merge(right_node, old_r);
            l = t;
            l->p = nullptr;
        }
    }
}

int getPos(pNode node) {
    vector<pNode> path;
    pNode cur = node;
    while (cur) {
        path.push_back(cur);
        cur = cur->p;
    }
    for (int i = (int)path.size() - 1; i >= 0; --i) {
        push(path[i]);
    }
    int res = (node->l ? node->l->sz : 0) + 1;
    cur = node;
    while (cur->p) {
        if (cur == cur->p->r) {
            res += (cur->p->l ? cur->p->l->sz : 0) + cur->p->len;
        }
        cur = cur->p;
    }
    return res;
}

void deleteTree(pNode t) {
    if (!t) return;
    deleteTree(t->l);
    deleteTree(t->r);
    delete t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    while (cin >> N >> Q) {
        docMap.clear();
        pNode root = new Node(1, 1, N, rand_pri());
        docMap[1] = root;

        for (int i = 0; i < Q; ++i) {
            int type;
            cin >> type;
            if (type == 0) {
                int L, R;
                cin >> L >> R;
                pNode left, mid, right;
                split(root, L - 1, left, mid);
                split(mid, R - L + 1, mid, right);
                if (mid) mid->rev ^= true;
                root = merge(left, merge(mid, right));
            } else {
                int x;
                cin >> x;
                auto it = docMap.upper_bound(x);
                --it;
                pNode node = it->second;
                int pos = getPos(node);
                int offset = (x - node->start_val) * node->step;
                cout << pos + offset << '\n';
            }
        }
        deleteTree(root);
    }
    return 0;
}
