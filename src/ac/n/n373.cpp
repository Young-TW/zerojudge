#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;            // number on the top bill
    int order;          // k, size = 2^k
    Node *child;        // leftmost child
    Node *sibling;      // next sibling
    explicit Node(int k) : key(k), order(0), child(nullptr), sibling(nullptr) {}
};

const int MAX_ORDER = 60;                 // enough for all constraints
Node* root[MAX_ORDER];                    // binomial heap roots, initially nullptr

// merge two trees of the same order, return the new root
Node* mergeSame(Node *a, Node *b) {
    if (a->key > b->key) swap(a, b);
    b->sibling = a->child;
    a->child = b;
    ++a->order;
    return a;
}

// insert a whole tree into the heap
void insertTree(Node *t) {
    int k = t->order;
    while (root[k]) {
        t = mergeSame(t, root[k]);
        root[k] = nullptr;
        ++k;
    }
    root[k] = t;
}

// erase the tree that is the 'rank'-th (1‑based) when ordered by size
void eraseByRank(int rank) {
    int cnt = 0, k = -1;
    for (int i = 0; i < MAX_ORDER; ++i) {
        if (root[i]) {
            ++cnt;
            if (cnt == rank) { k = i; break; }
        }
    }
    Node *t = root[k];
    root[k] = nullptr;                     // remove the whole tree

    // collect children (orders k-1 .. 0)
    vector<Node*> childs;
    for (Node *c = t->child; c; c = c->sibling) childs.push_back(c);
    reverse(childs.begin(), childs.end()); // now 0 .. k-1

    for (Node *c : childs) {
        c->sibling = nullptr;              // detach
        insertTree(c);
    }
    delete t;                              // free memory (optional)
}

// output current state
void outputState() {
    int m = 0;
    for (int i = 0; i < MAX_ORDER; ++i) if (root[i]) ++m;
    cout << m;
    for (int i = 0; i < MAX_ORDER; ++i)
        if (root[i]) cout << ' ' << root[i]->key;
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    for (int i = 0; i < MAX_ORDER; ++i) root[i] = nullptr;

    for (int i = 0; i < N; ++i) {
        long long x;
        cin >> x;
        if (x >= 0) {                       // insert a new bill
            Node *node = new Node((int)x);
            insertTree(node);
        } else {                            // take the -x-th book
            eraseByRank((int)(-x));
        }
        outputState();
    }
    return 0;
}
