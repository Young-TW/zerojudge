#include <bits/stdc++.h>
using namespace std;

const int MAXV = 100000;

struct SegNode {
    int l = 0, r = 0;
    int sum = 0;
} segPool[12000000];          // 足夠大的池子，視實際需求可調
int segPtr = 1;               // 0 表示空

int newSeg() {
    return segPtr++;
}

// persistent point update: add delta at position pos
int segAdd(int cur, int l, int r, int pos, int delta) {
    int nd = newSeg();
    segPool[nd] = segPool[cur];
    segPool[nd].sum += delta;
    if (l != r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) segPool[nd].l = segAdd(segPool[cur].l, l, mid, pos, delta);
        else            segPool[nd].r = segAdd(segPool[cur].r, mid + 1, r, pos, delta);
    }
    return nd;
}

// merge two persistent segment trees
int segMerge(int a, int b, int l, int r) {
    if (!a) return b;
    if (!b) return a;
    int nd = newSeg();
    if (l == r) {
        segPool[nd].sum = segPool[a].sum + segPool[b].sum;
    } else {
        int mid = (l + r) >> 1;
        segPool[nd].l = segMerge(segPool[a].l, segPool[b].l, l, mid);
        segPool[nd].r = segMerge(segPool[a].r, segPool[b].r, mid + 1, r);
        int leftSum  = segPool[nd].l ? segPool[segPool[nd].l].sum : 0;
        int rightSum = segPool[nd].r ? segPool[segPool[nd].r].sum : 0;
        segPool[nd].sum = leftSum + rightSum;
    }
    return nd;
}

// kth smallest in a segment tree
int segKth(int nd, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int leftSum = segPool[segPool[nd].l].sum;
    if (k <= leftSum) return segKth(segPool[nd].l, l, mid, k);
    else return segKth(segPool[nd].r, mid + 1, r, k - leftSum);
}

/* ---------- Persistent Treap ---------- */
struct Node {
    int val;
    int pr;
    int sz;
    int seg;      // root index of segment tree for subtree
    Node *l, *r;
    Node(int v = 0, int p = 0) : val(v), pr(p), sz(1), seg(0), l(nullptr), r(nullptr) {}
};

vector<Node*> nodePool;
int nodePtr = 0;

Node* newNode(int v) {
    Node* nd = new Node(v, (rand() << 16) ^ rand());
    nodePool.push_back(nd);
    return nd;
}

int getSize(Node* t) { return t ? t->sz : 0; }
int getSeg(Node* t) { return t ? t->seg : 0; }

Node* clone(Node* t) {
    if (!t) return nullptr;
    Node* nd = newNode(t->val);
    nd->pr = t->pr;
    nd->l = t->l;
    nd->r = t->r;
    nd->sz = t->sz;
    nd->seg = t->seg;
    return nd;
}

Node* upd(Node* t) {
    if (!t) return nullptr;
    t->sz = 1 + getSize(t->l) + getSize(t->r);
    int merged = segMerge(getSeg(t->l), getSeg(t->r), 1, MAXV);
    t->seg = segAdd(merged, 1, MAXV, t->val, 1);
    return t;
}

// split first k nodes to a, rest to b
void split(Node* t, int k, Node* &a, Node* &b) {
    if (!t) { a = b = nullptr; return; }
    t = clone(t);
    int leftSize = getSize(t->l);
    if (k <= leftSize) {
        split(t->l, k, a, t->l);
        b = t;
        upd(b);
    } else {
        split(t->r, k - leftSize - 1, t->r, b);
        a = t;
        upd(a);
    }
}

Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->pr < b->pr) {
        a = clone(a);
        a->r = merge(a->r, b);
        return upd(a);
    } else {
        b = clone(b);
        b->l = merge(a, b->l);
        return upd(b);
    }
}

/* ---------- Main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)chrono::steady_clock::now().time_since_epoch().count());

    int n;
    if (!(cin >> n)) return 0;
    vector<int> init(n);
    for (int i = 0; i < n; ++i) cin >> init[i];

    Node* root0 = nullptr;
    for (int i = 0; i < n; ++i) {
        Node* nd = newNode(init[i]);
        nd->seg = segAdd(0, 1, MAXV, init[i], 1);
        root0 = merge(root0, nd);
    }

    int q;
    cin >> q;
    vector<Node*> version(q + 1);
    version[0] = root0;
    int lastAns = 0;

    for (int day = 1; day <= q; ++day) {
        long long raw;
        cin >> raw;
        int t = (int)(raw ^ lastAns);
        if (t == 0) {                     // revert
            cin >> raw;
            int k = (int)(raw ^ lastAns);
            version[day] = version[k];
        } else if (t == 1) {              // insert
            long long rx, rv;
            cin >> rx >> rv;
            int x = (int)(rx ^ lastAns);
            int v = (int)(rv ^ lastAns);
            Node *L, *R;
            split(version[day - 1], x, L, R);   // first x elements to L
            Node* nd = newNode(v);
            nd->seg = segAdd(0, 1, MAXV, v, 1);
            Node* merged = merge(L, nd);
            version[day] = merge(merged, R);
        } else if (t == 2) {              // delete
            cin >> raw;
            int x = (int)(raw ^ lastAns);
            Node *L, *midR;
            split(version[day - 1], x - 1, L, midR);
            Node *mid, *R;
            split(midR, 1, mid, R);   // mid is the node to delete
            version[day] = merge(L, R);
        } else if (t == 3) {              // modify
            long long rx, rv;
            cin >> rx >> rv;
            int x = (int)(rx ^ lastAns);
            int v = (int)(rv ^ lastAns);
            Node *L, *midR;
            split(version[day - 1], x - 1, L, midR);
            Node *mid, *R;
            split(midR, 1, mid, R);
            // create new node with value v
            Node* nd = newNode(v);
            nd->seg = segAdd(0, 1, MAXV, v, 1);
            Node* merged = merge(L, nd);
            version[day] = merge(merged, R);
        } else if (t == 4) {              // query kth smallest
            long long rx, ry, rk;
            cin >> rx >> ry >> rk;
            int x = (int)(rx ^ lastAns);
            int y = (int)(ry ^ lastAns);
            int k = (int)(rk ^ lastAns);
            Node *L, *midR;
            split(version[day - 1], x - 1, L, midR);
            Node *mid, *R;
            split(midR, y - x + 1, mid, R);
            int ans = segKth(mid->seg, 1, MAXV, k);
            cout << ans << '\n';
            lastAns = ans;
            // reassemble to keep version unchanged (since query does not modify)
            Node* tmp = merge(mid, R);
            version[day] = merge(L, tmp);
        } else {
            // 不會發生
            version[day] = version[day - 1];
        }
    }
    return 0;
}
