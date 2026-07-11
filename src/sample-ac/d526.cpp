#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        Node* root = nullptr;
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            if (!root) {
                root = new Node(x);
            } else {
                Node* cur = root;
                while (true) {
                    if (x < cur->val) {
                        if (cur->left) {
                            cur = cur->left;
                        } else {
                            cur->left = new Node(x);
                            break;
                        }
                    } else {
                        if (cur->right) {
                            cur = cur->right;
                        } else {
                            cur->right = new Node(x);
                            break;
                        }
                    }
                }
            }
        }
        
        vector<int> res;
        stack<Node*> st;
        if (root) st.push(root);
        while (!st.empty()) {
            Node* cur = st.top();
            st.pop();
            res.push_back(cur->val);
            if (cur->right) st.push(cur->right);
            if (cur->left) st.push(cur->left);
        }
        
        for (size_t i = 0; i < res.size(); ++i) {
            cout << res[i] << (i == res.size() - 1 ? "" : " ");
        }
        cout << "\n";
        
        stack<Node*> cleanup;
        if (root) cleanup.push(root);
        while (!cleanup.empty()) {
            Node* cur = cleanup.top();
            cleanup.pop();
            if (cur->left) cleanup.push(cur->left);
            if (cur->right) cleanup.push(cur->right);
            delete cur;
        }
    }
    
    return 0;
}
