#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parent[10005];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra != rb) {
        if (ra < rb)
            parent[rb] = ra;
        else
            parent[ra] = rb;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++)
            parent[i] = i;
        
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            unite(a, b);
        }
        
        vector<int> roots;
        for (int i = 1; i <= n; i++) {
            if (find(i) == i)
                roots.push_back(i);
        }
        
        sort(roots.begin(), roots.end());
        
        cout << "[";
        for (size_t i = 0; i < roots.size(); i++) {
            if (i > 0) cout << ", ";
            cout << roots[i];
        }
        cout << "]" << endl;
    }
    
    return 0;
}
