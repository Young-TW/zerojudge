#include <iostream>
#include <vector>

using namespace std;

class DSU {
public:
    vector<int> parent;
    vector<int> rank_;
    
    DSU(int n) {
        parent.resize(n);
        rank_.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank_[root_i] < rank_[root_j]) {
                parent[root_i] = root_j;
            } else if (rank_[root_i] > rank_[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank_[root_i]++;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k) {
        DSU dsu(n);
        for (int i = 0; i < k; ++i) {
            int a, b;
            cin >> a >> b;
            dsu.unite(a, b);
        }
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (dsu.find(i) == i) {
                count++;
            }
        }
        cout << count << "\n";
    }
    return 0;
}
