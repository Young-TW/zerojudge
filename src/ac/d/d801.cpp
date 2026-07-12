#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

const int INF = 2e9;

struct Node {
    int val;
    unsigned int priority;
    int size;
    int min_val;
    int max_val;
    Node* left;
    Node* right;
    
    Node() {}
    Node(int v, unsigned int p) : val(v), priority(p), size(1), min_val(v), max_val(v), left(nullptr), right(nullptr) {}
};

int get_size(Node* node) {
    return node ? node->size : 0;
}

void push_up(Node* node) {
    if (node) {
        node->size = 1 + get_size(node->left) + get_size(node->right);
        node->min_val = node->val;
        node->max_val = node->val;
        if (node->left) {
            node->min_val = min(node->min_val, node->left->min_val);
            node->max_val = max(node->max_val, node->left->max_val);
        }
        if (node->right) {
            node->min_val = min(node->min_val, node->right->min_val);
            node->max_val = max(node->max_val, node->right->max_val);
        }
    }
}

void split(Node* root, int k, Node*& x, Node*& y) {
    if (!root) {
        x = y = nullptr;
        return;
    }
    int left_size = get_size(root->left);
    if (left_size < k) {
        x = root;
        split(root->right, k - left_size - 1, root->right, y);
        push_up(x);
    } else {
        y = root;
        split(root->left, k, x, root->left);
        push_up(y);
    }
}

Node* merge(Node* x, Node* y) {
    if (!x || !y) return x ? x : y;
    if (x->priority > y->priority) {
        x->right = merge(x->right, y);
        push_up(x);
        return x;
    } else {
        y->left = merge(x, y->left);
        push_up(y);
        return y;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<Node> pool;
        pool.reserve(n + 5);
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        
        Node* root = nullptr;
        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            pool.push_back(Node(val, rng()));
            root = merge(root, &pool.back());
        }
        
        for (int i = 0; i < m; ++i) {
            int op;
            cin >> op;
            if (op == 1) {
                int k;
                cin >> k;
                Node *x, *y, *z;
                split(root, k - 1, x, y);
                split(y, 1, z, y);
                root = merge(x, y);
            } else if (op == 2) {
                int l, r;
                cin >> l >> r;
                Node *x, *y, *z;
                split(root, l - 1, x, y);
                split(y, r - l + 1, z, y);
                cout << z->min_val << " " << z->max_val << "\n";
                root = merge(x, merge(z, y));
            }
        }
    }
    
    return 0;
}
