#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->val << "\n";
    inorder(root->right);
}

bool search(Node* root, int val) {
    if (root == nullptr) return false;
    if (root->val == val) return true;
    if (val < root->val) return search(root->left, val);
    return search(root->right, val);
}

void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        Node* root = nullptr;
        for (int i = 0; i < N; ++i) {
            int a;
            cin >> a;
            root = insert(root, a);
        }
        
        inorder(root);
        
        int q;
        cin >> q;
        if (search(root, q)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
        
        freeTree(root);
    }
    
    return 0;
}
