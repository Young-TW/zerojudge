#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int parent[81];

void init() {
    for (int i = 0; i < 81; ++i) {
        parent[i] = i;
    }
}

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss_n(line);
        int n;
        if (!(ss_n >> n)) continue;
        
        for (int i = 0; i < n; ++i) {
            string graph_line;
            if (!getline(cin, graph_line)) break;
            
            init();
            bool is_tree = true;
            bool visited[81] = {false};
            int node_count = 0;
            
            stringstream ss(graph_line);
            string edge;
            while (ss >> edge) {
                size_t comma_pos = edge.find(',');
                if (comma_pos == string::npos) continue;
                int u = stoi(edge.substr(0, comma_pos));
                int v = stoi(edge.substr(comma_pos + 1));
                
                if (u < 0 || u > 80 || v < 0 || v > 80) {
                    is_tree = false;
                    continue;
                }
                
                if (!visited[u]) {
                    visited[u] = true;
                    node_count++;
                }
                if (!visited[v]) {
                    visited[v] = true;
                    node_count++;
                }
                
                if (u == v) {
                    is_tree = false;
                } else if (find(u) == find(v)) {
                    is_tree = false;
                } else {
                    unite(u, v);
                }
            }
            
            if (node_count == 0) {
                is_tree = false;
            } else {
                int root = -1;
                for (int j = 0; j < 81; ++j) {
                    if (visited[j]) {
                        if (root == -1) {
                            root = find(j);
                        } else if (find(j) != root) {
                            is_tree = false;
                            break;
                        }
                    }
                }
            }
            
            cout << (is_tree ? 'T' : 'F') << '\n';
        }
    }
    
    return 0;
}
