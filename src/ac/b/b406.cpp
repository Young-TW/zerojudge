#include <bits/stdc++.h>
using namespace std;

/* ---------- persistent treap ---------- */

struct Node {
    char ch;
    int pri;
    int sz;
    int l, r;
    Node() : ch(0), pri(0), sz(0), l(0), r(0) {}
    Node(char c, int p) : ch(c), pri(p), sz(1), l(0), r(0) {}
};

const int MAXNODE = 6000000;          // enough for all test data
Node pool[MAXNODE];
int poolPtr = 1;                      // 0 is the null node

inline int new_node(char c) {
    int id = poolPtr++;
    pool[id] = Node(c, (int)rand());
    return id;
}
inline int clone_node(int t) {
    int id = poolPtr++;
    pool[id] = pool[t];
    return id;
}
inline int sz(int t) { return t ? pool[t].sz : 0; }
inline void upd(int t) {
    if (t) pool[t].sz = 1 + sz(pool[t].l) + sz(pool[t].r);
}

/* merge two treaps, all keys in a are before keys in b */
int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    if (pool[a].pri > pool[b].pri) {
        int na = clone_node(a);
        pool[na].r = merge(pool[a].r, b);
        upd(na);
        return na;
    } else {
        int nb = clone_node(b);
        pool[nb].l = merge(a, pool[b].l);
        upd(nb);
        return nb;
    }
}

/* split treap t into a (first k characters) and b (rest) */
void split(int t, int k, int &a, int &b) {
    if (!t) { a = b = 0; return; }
    int leftSize = sz(pool[t].l);
    if (k <= leftSize) {
        // split in left subtree
        int a1, b1;
        split(pool[t].l, k, a1, b1);
        int nt = clone_node(t);
        pool[nt].l = b1;
        upd(nt);
        a = a1;
        b = nt;
    } else {
        // split in right subtree (skip left + root)
        int a1, b1;
        split(pool[t].r, k - leftSize - 1, a1, b1);
        int nt = clone_node(t);
        pool[nt].r = a1;
        upd(nt);
        a = nt;
        b = b1;
    }
}

/* build a treap from a string (linear, using merges) */
int build_from_string(const string &s) {
    int cur = 0;
    for (char c : s) {
        cur = merge(cur, new_node(c));
    }
    return cur;
}

/* insert string s after position p (0‑based count of characters kept on left) */
int insert_str(int root, int p, const string &s) {
    int left, right;
    split(root, p, left, right);
    int mid = build_from_string(s);
    return merge(merge(left, mid), right);
}

/* delete c characters starting at position p (1‑based) */
int delete_range(int root, int p, int c) {
    int left, tmp;
    split(root, p - 1, left, tmp);
    int mid, right;
    split(tmp, c, mid, right);   // mid is discarded
    return merge(left, right);
}

/* collect characters in [l, r] (1‑based) */
void collect(int t, int l, int r, int add, string &out) {
    if (!t) return;
    int curPos = add + sz(pool[t].l) + 1;
    if (l < curPos) collect(pool[t].l, l, r, add, out);
    if (l <= curPos && curPos <= r) out.push_back(pool[t].ch);
    if (curPos < r) collect(pool[t].r, l, r, curPos, out);
}

/* ---------- main ---------- */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)chrono::steady_clock::now().time_since_epoch().count());

    int n;
    while (cin >> n) {
        vector<int> root(n + 2, 0);   // root[version]
        int vnow = 0;
        int d = 0;                    // number of printed 'c' so far

        for (int i = 0; i < n; ++i) {
            int type;
            cin >> type;
            if (type == 1) {                     // insert
                int p_obf;
                string s;
                cin >> p_obf >> s;
                int p = p_obf - d;                // deobfuscate
                ++vnow;
                root[vnow] = insert_str(root[vnow - 1], p, s);
            } else if (type == 2) {              // delete
                int p_obf, c_obf;
                cin >> p_obf >> c_obf;
                int p = p_obf - d;
                int c = c_obf - d;
                ++vnow;
                root[vnow] = delete_range(root[vnow - 1], p, c);
            } else {                              // query
                int v_obf, p_obf, c_obf;
                cin >> v_obf >> p_obf >> c_obf;
                int v = v_obf - d;
                int p = p_obf - d;
                int c = c_obf - d;
                string ans;
                if (c > 0)
                    collect(root[v], p, p + c - 1, 0, ans);
                cout << ans << '\n';
                for (char ch : ans) if (ch == 'c') ++d;
            }
        }
    }
    return 0;
}
