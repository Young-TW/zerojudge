#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<long long> weight(2 * n, 0);
        for (int i = n; i < 2 * n; ++i) {
            cin >> weight[i];
        }
        
        vector<long long> goods(m);
        for (int i = 0; i < m; ++i) {
            cin >> goods[i];
        }
        
        vector<int> left_child(n, 0);
        vector<int> right_child(n, 0);
        vector<int> parent(2 * n, 0);
        
        for (int i = 0; i < n - 1; ++i) {
            int p, s, t;
            cin >> p >> s >> t;
            left_child[p] = s;
            right_child[p] = t;
            parent[s] = p;
            parent[t] = p;
        }
        
        vector<long long> subtree_weight(2 * n, 0);
        for (int i = n; i < 2 * n; ++i) {
            subtree_weight[i] = weight[i];
        }
        
        vector<int> stk;
        vector<int> state(2 * n, 0);
        stk.push_back(1);
        while (!stk.empty()) {
            int u = stk.back();
            if (u >= n) {
                stk.pop_back();
                continue;
            }
            if (state[u] == 0) {
                state[u] = 1;
                stk.push_back(left_child[u]);
            } else if (state[u] == 1) {
                state[u] = 2;
                stk.push_back(right_child[u]);
            } else {
                subtree_weight[u] = subtree_weight[left_child[u]] + subtree_weight[right_child[u]];
                stk.pop_back();
            }
        }
        
        for (int i = 0; i < m; ++i) {
            long long w = goods[i];
            int u = 1;
            while (u < n) {
                if (subtree_weight[left_child[u]] <= subtree_weight[right_child[u]]) {
                    u = left_child[u];
                } else {
                    u = right_child[u];
                }
            }
            if (i > 0) cout << " ";
            cout << u;
            
            while (u != 0) {
                subtree_weight[u] += w;
                u = parent[u];
            }
        }
        cout << "\n";
    }
    
    return 0;
}
