#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct Node {
    int parent;
    vector<int> children;
    int invaders;
    int subtree_sum;
    bool is_connected;
};

vector<Node> tree;
vector<int> parent_arr;

void dfs(int u) {
    tree[u].subtree_sum = tree[u].invaders;
    for (int v : tree[u].children) {
        if (v != tree[u].parent) {
            dfs(v);
            tree[u].subtree_sum += tree[v].subtree_sum;
        }
    }
}

int find_root(int u) {
    if (parent_arr[u] == u) return u;
    return parent_arr[u] = find_root(parent_arr[u]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        tree.resize(N + 1);
        parent_arr.resize(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> tree[i].invaders;
            tree[i].parent = 0;
            tree[i].children.clear();
            tree[i].subtree_sum = 0;
            tree[i].is_connected = false;
            parent_arr[i] = i;
        }

        for (int i = 0; i < M; ++i) {
            int op;
            cin >> op;
            if (op == 1) {
                int u, v;
                cin >> u >> v;
                int root_u = find_root(u);
                int root_v = find_root(v);
                if (root_u != root_v) {
                    parent_arr[root_u] = root_v;
                    tree[v].children.push_back(u);
                    tree[u].parent = v;
                    tree[u].is_connected = true;
                }
            } else if (op == 2) {
                int u;
                cin >> u;
                if (tree[u].is_connected) {
                    int v = tree[u].parent;
                    tree[v].children.erase(remove(tree[v].children.begin(), tree[v].children.end(), u), tree[v].children.end());
                    tree[u].parent = 0;
                    tree[u].is_connected = false;
                    parent_arr[u] = u;
                }
            } else if (op == 3) {
                int u, w;
                cin >> u >> w;
                int diff = w - tree[u].invaders;
                tree[u].invaders = w;
                for (int cur = u; cur != 0; cur = tree[cur].parent) {
                    tree[cur].subtree_sum += diff;
                }
            } else if (op == 4) {
                int u;
                cin >> u;
                int root = find_root(u);
                dfs(root);
                cout << tree[u].subtree_sum << '\n';
            }
        }
    }

    return 0;
}
