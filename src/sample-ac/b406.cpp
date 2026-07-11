#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;

const int MAXN = 5000000;

struct Node {
    char val;
    int pri, sz;
    int l, r;
    Node() : val(0), pri(0), sz(0), l(0), r(0) {}
    Node(char v, int p) : val(v), pri(p), sz(1), l(0), r(0) {}
};

Node pool[MAXN];
int pool_ptr = 1;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int new_node(char v) {
    int id = pool_ptr++;
    pool[id] = Node(v, (int)rng());
    return id;
}

inline int clone(int t) {
    int id = pool_ptr++;
    pool[id] = pool[t];
    return id;
}

inline int get_size(int t) {
    return t ? pool[t].sz : 0;
}

inline void update(int t) {
    if (t) pool[t].sz = 1 + get_size(pool[t].l) + get_size(pool[t].r);
}

int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    if (pool[a].pri > pool[b].pri) {
        int new_a = clone(a);
        pool[new_a].r = merge(pool[a].r, b);
        update(new_a);
        return new_a;
    } else {
        int new_b = clone(b);
        pool[new_b].l = merge(a, pool[b].l);
        update(new_b);
        return new_b;
    }
}

void split(int t, int k, int& a, int& b) {
    if (!t) {
        a = b = 0;
        return;
    }
    int sz = get_size(t);
    if (k <= 0) {
        a = 0;
        b = t;
        return;
    }
    if (k >= sz) {
        a = t;
        b = 0;
        return;
    }
    int left_sz = get_size(pool[t].l);
    if (k < left_sz) {
        int new_t = clone(t);
        split(pool[t].l, k, a, pool[new_t].l);
        b = new_t;
        update(b);
    } else if (k > left_sz) {
        int new_t = clone(t);
        split(pool[t].r, k - left_sz - 1, pool[new_t].r, b);
        a = new_t;
        update(a);
    } else { // k == left_sz
        a = pool[t].l;
        int new_b = clone(t);
        pool[new_b].l = 0;
        update(new_b);
        b = new_b;
    }
}

int build(const string& s) {
    int res = 0;
    for (char c : s) {
        res = merge(res, new_node(c));
    }
    return res;
}

int insert(int root, int p, const string& s) {
    int left, right;
    split(root, p, left, right);
    int mid = build(s);
    int merged = merge(left, mid);
    return merge(merged, right);
}

int delete_range(int root, int p, int c) {
    int left, mid_right;
    split(root, p - 1, left, mid_right);
    int mid, right;
    split(mid_right, c, mid, right);
    return merge(left, right);
}

void collect(int t, int l, int r, int add, string& res) {
    if (!t) return;
    int sz = get_size(t);
    if (add + sz < l) return;
    if (add + 1 > r) return;
    int left_sz = get_size(pool[t].l);
    int cur_pos = add + left_sz + 1;
    if (cur_pos > r) {
        collect(pool[t].l, l, r, add, res);
        return;
    }
    if (cur_pos < l) {
        collect(pool[t].r, l, r, cur_pos, res);
        return;
    }
    collect(pool[t].l, l, r, add, res);
    res.push_back(pool[t].val);
    collect(pool[t].r, l, r, cur_pos, res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        pool_ptr = 1;
        vector<int> roots(n + 1);
        roots[0] = 0;
        int vnow = 0;
        int d = 0;
        
        for (int i = 0; i < n; ++i) {
            int type;
            cin >> type;
            if (type == 1) {
                int p_obf;
                string s;
                cin >> p_obf >> s;
                int p = p_obf - d;
                roots[++vnow] = insert(roots[vnow], p, s);
            } else if (type == 2) {
                int p_obf, c_obf;
                cin >> p_obf >> c_obf;
                int p = p_obf - d;
                int c = c_obf - d;
                roots[++vnow] = delete_range(roots[vnow], p, c);
            } else if (type == 3) {
                int v_obf, p_obf, c_obf;
                cin >> v_obf >> p_obf >> c_obf;
                int v = v_obf - d;
                int p = p_obf - d;
                int c = c_obf - d;
                string res;
                if (c > 0) {
                    collect(roots[v], p, p + c - 1, 0, res);
                }
                cout << res << '\n';
                for (char ch : res) {
                    if (ch == 'c') d++;
                }
            }
        }
    }
    return 0;
}
