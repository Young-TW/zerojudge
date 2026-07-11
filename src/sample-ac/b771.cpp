#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cstdlib>

using namespace std;

mt19937 rng(1337);

struct Node {
    int l, r;
    int size;
    unsigned int rnd;
    char val;
    Node() : l(0), r(0), size(0), rnd(0), val(0) {}
    Node(char v) : l(0), r(0), size(1), rnd(rng()), val(v) {}
};

vector<Node> pool(1);

int newNode(char v) {
    pool.push_back(Node(v));
    return pool.size() - 1;
}

int get_size(int t) {
    return t ? pool[t].size : 0;
}

void update(int t) {
    if (t) {
        pool[t].size = 1 + get_size(pool[t].l) + get_size(pool[t].r);
    }
}

void split(int t, int k, int& x, int& y) {
    if (!t) {
        x = y = 0;
        return;
    }
    if (get_size(pool[t].l) < k) {
        x = t;
        split(pool[t].r, k - get_size(pool[t].l) - 1, pool[t].r, y);
    } else {
        y = t;
        split(pool[t].l, k, x, pool[t].l);
    }
    update(t);
}

int merge(int x, int y) {
    if (!x || !y) return x ? x : y;
    if (pool[x].rnd > pool[y].rnd) {
        pool[x].r = merge(pool[x].r, y);
        update(x);
        return x;
    } else {
        pool[y].l = merge(x, pool[y].l);
        update(y);
        return y;
    }
}

int root = 0;

void insert(int k, char val) {
    int x, y;
    split(root, k, x, y);
    root = merge(merge(x, newNode(val)), y);
}

void delete_node(int k) {
    int x, y, z;
    split(root, k, x, y);
    split(y, 1, y, z);
    root = merge(x, z);
}

void inorder(int t, string& s) {
    if (!t) return;
    inorder(pool[t].l, s);
    s += pool[t].val;
    inorder(pool[t].r, s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    pool.reserve(1000005);
    
    string cmd;
    while (cin >> cmd) {
        if (cmd == "insert") {
            string pos;
            cin >> pos;
            char x;
            if (pos == "left") {
                cin >> x;
                insert(0, x);
            } else if (pos == "right") {
                cin >> x;
                insert(get_size(root), x);
            } else {
                int k = atoi(pos.c_str());
                cin >> x;
                insert(k - 1, x);
            }
        } else if (cmd == "delete") {
            string pos;
            cin >> pos;
            if (pos == "left") {
                delete_node(0);
            } else if (pos == "right") {
                delete_node(get_size(root) - 1);
            } else {
                int k = atoi(pos.c_str());
                delete_node(k - 1);
            }
        }
    }
    
    string s;
    s.reserve(get_size(root));
    inorder(root, s);
    
    if (s.empty()) {
        cout << 0 << "\n";
        return 0;
    }
    
    int max_len = 0;
    int curr_len = 1;
    for (int i = 1; i < (int)s.length(); ++i) {
        if (s[i] == s[i-1]) {
            curr_len++;
        } else {
            max_len = max(max_len, curr_len);
            curr_len = 1;
        }
    }
    max_len = max(max_len, curr_len);
    
    vector<char> ans_chars;
    curr_len = 1;
    for (int i = 1; i < (int)s.length(); ++i) {
        if (s[i] == s[i-1]) {
            curr_len++;
        } else {
            if (curr_len == max_len) {
                ans_chars.push_back(s[i-1]);
            }
            curr_len = 1;
        }
    }
    if (curr_len == max_len) {
        ans_chars.push_back(s.back());
    }
    
    for (char c : ans_chars) {
        cout << c << " ";
    }
    cout << max_len << "\n";
    
    return 0;
}
