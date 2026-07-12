#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

struct Node {
    int val, mx;
    int sz;
    unsigned int pri;
    Node *l, *r;
    Node() {}
    Node(int v, unsigned int p) : val(v), mx(v), sz(1), pri(p), l(nullptr), r(nullptr) {}
};

const int MAXN = 100005;
Node pool[MAXN];
int pool_cnt = 0;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int get_sz(Node* t) { return t ? t->sz : 0; }
int get_mx(Node* t) { return t ? t->mx : 0; }

void pull(Node* t) {
    if (t) {
        t->sz = 1 + get_sz(t->l) + get_sz(t->r);
        t->mx = max({t->val, get_mx(t->l), get_mx(t->r)});
    }
}

void split(Node* t, int k, Node*& a, Node*& b) {
    if (!t) { a = b = nullptr; return; }
    if (get_sz(t->l) < k) {
        a = t;
        split(t->r, k - get_sz(t->l) - 1, a->r, b);
        pull(a);
    } else {
        b = t;
        split(t->l, k, a, b->l);
        pull(b);
    }
}

Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
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

Node* build(const vector<int>& arr) {
    Node* root = nullptr;
    for (int x : arr) {
        pool[pool_cnt] = Node(x, rng());
        root = merge(root, &pool[pool_cnt]);
        pool_cnt++;
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    while (cin >> n >> q) {
        pool_cnt = 0;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        
        Node* root = build(arr);
        
        while (q--) {
            int ty, l, r;
            cin >> ty >> l >> r;
            
            Node *a, *b, *c;
            split(root, l - 1, a, b);
            split(b, r - l + 1, b, c);
            
            if (ty == 1) {
                root = merge(b, merge(a, c));
            } else if (ty == 2) {
                root = merge(a, merge(c, b));
            } else {
                cout << get_mx(b) << "\n";
                root = merge(a, merge(b, c));
            }
        }
    }
    
    return 0;
}
