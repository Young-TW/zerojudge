#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};

class DSU {
public:
    vector<int> parent, rank_;
    DSU(int n) {
        parent.resize(n);
        rank_.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j)
            return false;
        if (rank_[root_i] < rank_[root_j]) {
            parent[root_i] = root_j;
        } else if (rank_[root_i] > rank_[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank_[root_i]++;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, r;
    int scenario_num = 1;
    while (cin >> n >> r) {
        if (n == 0 && r == 0) break;
        
        map<string, int> city_to_id;
        int city_count = 0;
        vector<Edge> edges(r);
        
        auto get_id = [&](const string& name) {
            if (city_to_id.find(name) == city_to_id.end()) {
                city_to_id[name] = city_count++;
            }
            return city_to_id[name];
        };
        
        for (int i = 0; i < r; ++i) {
            string u_name, v_name;
            int w;
            cin >> u_name >> v_name >> w;
            edges[i] = {get_id(u_name), get_id(v_name), w};
        }
        
        string start_name, end_name;
        cin >> start_name >> end_name;
        int start_node = get_id(start_name);
        int end_node = get_id(end_name);
        
        sort(edges.begin(), edges.end());
        
        DSU dsu(n);
        int ans = 0;
        for (int i = 0; i < r; ++i) {
            dsu.unite(edges[i].u, edges[i].v);
            if (dsu.find(start_node) == dsu.find(end_node)) {
                ans = edges[i].w;
                break;
            }
        }
        
        cout << "Scenario #" << scenario_num++ << "\n";
        cout << ans << " tons\n\n";
    }
    
    return 0;
}
