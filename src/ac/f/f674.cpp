#include <iostream>
#include <vector>

using namespace std;

int left_child[35];
int right_child[35];

void preorder(int u, vector<int>& res) {
    if (u == -1) return;
    res.push_back(u);
    preorder(left_child[u], res);
    preorder(right_child[u], res);
}

void inorder(int u, vector<int>& res) {
    if (u == -1) return;
    inorder(left_child[u], res);
    res.push_back(u);
    inorder(right_child[u], res);
}

void postorder(int u, vector<int>& res) {
    if (u == -1) return;
    postorder(left_child[u], res);
    postorder(right_child[u], res);
    res.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            int u, a, b;
            cin >> u >> a >> b;
            left_child[u] = a;
            right_child[u] = b;
        }
        
        vector<int> pre, in, post;
        preorder(0, pre);
        inorder(0, in);
        postorder(0, post);
        
        for (size_t i = 0; i < pre.size(); ++i) {
            cout << pre[i] << (i + 1 == pre.size() ? "" : " ");
        }
        cout << "\n";
        for (size_t i = 0; i < in.size(); ++i) {
            cout << in[i] << (i + 1 == in.size() ? "" : " ");
        }
        cout << "\n";
        for (size_t i = 0; i < post.size(); ++i) {
            cout << post[i] << (i + 1 == post.size() ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
