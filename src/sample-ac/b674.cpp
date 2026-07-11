#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        int in_degree[1001];
        memset(in_degree, 0, sizeof(in_degree));
        vector<int> adj[1001];
        set<int> nodes;
        
        for (int i = 0; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            nodes.insert(u);
            nodes.insert(v);
            in_degree[v]++;
            adj[u].push_back(v);
        }
        
        int root = -1;
        bool valid = true;
        for (int node : nodes) {
            if (in_degree[node] == 0) {
                if (root != -1) {
                    valid = false;
                    break;
                }
                root = node;
            } else if (in_degree[node] > 1) {
                valid = false;
                break;
            }
        }
        
        if (!valid || root == -1) {
            cout << "n\n";
            continue;
        }
        
        vector<bool> visited(1001, false);
        int count = 0;
        vector<int> stk;
        stk.push_back(root);
        visited[root] = true;
        
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            count++;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    stk.push_back(v);
                } else {
                    valid = false;
                }
            }
        }
        
        if (valid && count == nodes.size()) {
            cout << "y\n";
        } else {
            cout << "n\n";
        }
    }
    
    return 0;
}
