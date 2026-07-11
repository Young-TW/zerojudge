#include <iostream>
#include <map>
#include <set>

using namespace std;

map<int, int> parent;
map<int, int> indegree;
set<int> nodes;

int find(int x) {
    if (parent.find(x) == parent.end()) {
        parent[x] = x;
        return x;
    }
    int root = x;
    while (parent[root] != root) {
        root = parent[root];
    }
    int curr = x;
    while (parent[curr] != root) {
        int next = parent[curr];
        parent[curr] = root;
        curr = next;
    }
    return root;
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) {
        parent[rx] = ry;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int u, v;
    int case_num = 1;
    bool is_tree = true;
    int edge_count = 0;
    
    while (cin >> u >> v) {
        if (u < 0 && v < 0) break;
        if (u == 0 && v == 0) {
            if (nodes.empty()) {
                cout << "Case " << case_num << " is a tree." << endl;
            } else {
                if (is_tree && edge_count == nodes.size() - 1) {
                    cout << "Case " << case_num << " is a tree." << endl;
                } else {
                    cout << "Case " << case_num << " is not a tree." << endl;
                }
            }
            case_num++;
            is_tree = true;
            edge_count = 0;
            parent.clear();
            indegree.clear();
            nodes.clear();
        } else {
            if (is_tree) {
                nodes.insert(u);
                nodes.insert(v);
                indegree[v]++;
                if (indegree[v] > 1) {
                    is_tree = false;
                }
                edge_count++;
                if (find(u) == find(v)) {
                    is_tree = false;
                } else {
                    unite(u, v);
                }
            }
        }
    }
    return 0;
}
