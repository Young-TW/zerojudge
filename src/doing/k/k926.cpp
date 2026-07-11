#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    int m;
    while (cin >> s >> t) {
        cin >> m;
        UnionFind uf(26);
        for (int i = 0; i < m; ++i) {
            char c1, c2;
            cin >> c1 >> c2;
            int u = c1 - 'a';
            int v = c2 - 'a';
            uf.unite(u, v);
        }
        int n = s.size();
        int mt = t.size();
        vector<int> prev(mt + 1), curr(mt + 1);
        for (int j = 0; j <= mt; ++j) prev[j] = j;
        for (int i = 1; i <= n; ++i) {
            curr[0] = i;
            for (int j = 1; j <= mt; ++j) {
                int cost = (uf.find(s[i-1] - 'a') == uf.find(t[j-1] - 'a')) ? 0 : 1;
                curr[j] = min({prev[j] + 1, curr[j-1] + 1, prev[j-1] + cost});
            }
            swap(prev, curr);
        }
        cout << prev[mt] << "\n";
    }
    return 0;
}
