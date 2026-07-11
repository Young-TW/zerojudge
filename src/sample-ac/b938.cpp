#include <iostream>
using namespace std;

int parent[1000005];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n + 1; i++) {
            parent[i] = i;
        }
        
        for (int i = 0; i < m; i++) {
            int k;
            cin >> k;
            
            if (find(k) != k) {
                cout << "0u0 ...... ?\n";
            } else {
                int victim = find(k + 1);
                if (victim > n) {
                    cout << "0u0 ...... ?\n";
                } else {
                    parent[victim] = find(victim + 1);
                    cout << victim << "\n";
                }
            }
        }
    }
    
    return 0;
}
