#include <iostream>
#include <string>
#include <random>
#include <vector>

using namespace std;

mt19937 rng(0x5EED);

struct Node {
    char c;
    int len;
    int size;
    unsigned int prio;
    Node *l, *r;
    Node(char _c, int _len) : c(_c), len(_len), size(_len), prio(rng()), l(nullptr), r(nullptr) {}
};

int sz(Node* t) { return t ? t->size : 0; }

void upd(Node* t) {
    if (t) t->size = t->len + sz(t->l) + sz(t->r);
}

Node* newNode(char c, int len) {
    return new Node(c, len);
}

void split(Node* t, int k, Node*& L, Node*& R) {
    if (!t) { L = R = nullptr; return; }
    if (k <= sz(t->l)) {
        split(t->l, k, L, t->l);
        R = t;
        upd(t);
    } else if (k >= sz(t->l) + t->len) {
        split(t->r, k - sz(t->l) - t->len, t->r, R);
        L = t;
        upd(t);
    } else {
        int left_len = k - sz(t->l);
        Node* right_node = newNode(t->c, t->len - left_len);
        right_node->r = t->r;
        upd(right_node);
        
        t->len = left_len;
        t->r = nullptr;
        upd(t);
        
        L = t;
        R = right_node;
    }
}

void merge(Node*& t, Node* L, Node* R) {
    if (!L || !R) { t = L ? L : R; return; }
    if (L->prio > R->prio) {
        merge(L->r, L->r, R);
        t = L;
    } else {
        merge(R->l, L, R->l);
        t = R;
    }
    upd(t);
}

Node* root = nullptr;

void print(Node* t) {
    char last_c = 0;
    int last_len = 0;
    vector<Node*> stk;
    Node* curr = t;
    while (curr || !stk.empty()) {
        while (curr) {
            stk.push_back(curr);
            curr = curr->l;
        }
        curr = stk.back();
        stk.pop_back();
        
        if (curr->c == last_c) {
            last_len += curr->len;
        } else {
            if (last_len > 0) {
                cout << last_c << " " << last_len << " ";
            }
            last_c = curr->c;
            last_len = curr->len;
        }
        
        curr = curr->r;
    }
    if (last_len > 0) {
        cout << last_c << " " << last_len << " ";
    }
    cout << "$\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string cmd;
    while (cin >> cmd) {
        if (cmd == "print") {
            print(root);
        } else if (cmd == "insert") {
            string next;
            cin >> next;
            char x;
            int n;
            if (next == "left") {
                cin >> x >> n;
                Node* node = newNode(x, n);
                merge(root, node, root);
            } else if (next == "right") {
                cin >> x >> n;
                Node* node = newNode(x, n);
                merge(root, root, node);
            } else {
                int k = stoi(next);
                cin >> x >> n;
                Node *L, *R;
                split(root, k - 1, L, R);
                Node* node = newNode(x, n);
                merge(L, L, node);
                merge(root, L, R);
            }
        }
    }
    return 0;
}
