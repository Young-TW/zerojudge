#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    bool first_tree_overall = true;
    while(cin >> N) {
        for(int t=0; t<N; ++t) {
            if(!first_tree_overall) {
                cout << "\n";
            }
            first_tree_overall = false;
            
            int m;
            cin >> m;
            vector<int> parent(m);
            vector<bool> has_child(m, false);
            char comma;
            for(int i=0; i<m; ++i) {
                int u, v;
                cin >> u >> comma >> v;
                parent[u] = v;
                if(v != 99) {
                    has_child[v] = true;
                }
            }
            for(int i=0; i<m; ++i) {
                if(!has_child[i]) {
                    vector<int> path;
                    int curr = parent[i];
                    while(curr != 99 && parent[curr] != 99) {
                        path.push_back(curr);
                        curr = parent[curr];
                    }
                    cout << i << ":";
                    if(path.empty()) {
                        cout << "N";
                    } else {
                        cout << "{";
                        for(size_t p=0; p<path.size(); ++p) {
                            if(p > 0) cout << ",";
                            cout << path[p];
                        }
                        cout << "}";
                    }
                    cout << "\n";
                }
            }
        }
    }
    return 0;
}
