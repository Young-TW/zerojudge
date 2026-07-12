#include <iostream>

using namespace std;

int parent[50005];
int rnk[50005];

void init(int n) {
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

bool unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        if (rnk[root_i] < rnk[root_j]) {
            parent[root_i] = root_j;
        } else if (rnk[root_i] > rnk[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rnk[root_i]++;
        }
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    int case_num = 1;
    
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        
        init(n);
        int ans = n;
        
        for (int k = 0; k < m; ++k) {
            int i, j;
            cin >> i >> j;
            if (unite(i, j)) {
                ans--;
            }
        }
        
        cout << "Case " << case_num << ": " << ans << "\n";
        case_num++;
    }
    
    return 0;
}
