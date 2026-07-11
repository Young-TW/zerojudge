#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<long long> L(m), R(m);
        bool possible = true;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                long long l, r;
                cin >> l >> r;
                if (i == 0) {
                    L[j] = l;
                    R[j] = r;
                } else {
                    L[j] = max(L[j], l);
                    R[j] = min(R[j], r);
                }
            }
        }
        
        for (int j = 0; j < m; ++j) {
            if (L[j] > R[j]) {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
