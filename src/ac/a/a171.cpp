#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long val;
    Node *left, *right;
    Node(long long v) : val(v), left(nullptr), right(nullptr) {}
};

/* insert into BST, ignore duplicates */
void insert(Node *&root, long long v) {
    if (!root) { root = new Node(v); return; }
    if (v == root->val) return;
    if (v < root->val) insert(root->left, v);
    else insert(root->right, v);
}

/* tree depth (number of levels) */
int depth(Node *root) {
    if (!root) return 0;
    return 1 + max(depth(root->left), depth(root->right));
}

/* global data for one test case */
int D;                              // depth
vector<int> h;                      // hi for each level (size D-1)
vector<int> rowIdx;                 // row number of each level
vector<tuple<int,long long,char>> elems;   // (row, col, ch)

/* recursive placement */
void dfs(Node *node, int lvl, long long col) {
    if (!node) return;
    int r = rowIdx[lvl];
    elems.emplace_back(r, col, 'X');

    if (lvl <= D - 2) {                 // there is a next level
        int hi = h[lvl];
        long long offset = hi + 1;      // horizontal distance to child

        if (node->left) {
            for (int s = 1; s <= hi; ++s)
                elems.emplace_back(r + s, col - s, '/');
            dfs(node->left, lvl + 1, col - offset);
        }
        if (node->right) {
            for (int s = 1; s <= hi; ++s)
                elems.emplace_back(r + s, col + s, '\\');
            dfs(node->right, lvl + 1, col + offset);
        }
    }
}

/* delete tree (not strictly necessary for the problem size) */
void clear(Node *root) {
    if (!root) return;
    clear(root->left);
    clear(root->right);
    delete root;
}

/* print one test case */
void printTree(Node *root) {
    D = depth(root);
    if (D == 0) return;                     // should not happen

    /* compute hi */
    h.assign(max(0, D - 1), 0);
    for (int i = 0; i <= D - 2; ++i) {
        int exp = D - i - 2;                // exponent for 2^(exp)
        h[i] = (exp >= 0) ? ((1 << exp) - 1) : 0;
    }

    /* compute row indices */
    rowIdx.assign(D, 0);
    for (int i = 1; i < D; ++i)
        rowIdx[i] = rowIdx[i - 1] + 1 + h[i - 1];

    elems.clear();
    dfs(root, 0, 0);                        // start at column 0

    /* find minimal column */
    long long minCol = LLONG_MAX;
    for (auto &t : elems) {
        int r; long long c; char ch;
        tie(r, c, ch) = t;
        if (c < minCol) minCol = c;
    }

    /* organise per row after shifting */
    map<int, map<int, char>> rows;          // row -> (col -> ch)
    for (auto &t : elems) {
        int r; long long c; char ch;
        tie(r, c, ch) = t;
        int cc = static_cast<int>(c - minCol);
        rows[r][cc] = ch;
    }

    int totalRows = 1 << (D - 1);           // 2^(D-1)

    for (int r = 0; r < totalRows; ++r) {
        auto it = rows.find(r);
        if (it == rows.end()) {
            cout << "\n";
            continue;
        }
        const auto &inner = it->second;
        int last = inner.rbegin()->first;
        string line(last + 1, ' ');
        for (auto &p : inner) line[p.first] = p.second;
        int pos = line.find_last_not_of(' ');
        if (pos == string::npos) cout << "\n";
        else cout << line.substr(0, pos + 1) << "\n";
    }
}

/* main driver – read until EOF */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        Node *root = nullptr;
        for (int i = 0; i < N; ++i) {
            long long v; cin >> v;
            insert(root, v);
        }
        printTree(root);
        clear(root);
    }
    return 0;
}
