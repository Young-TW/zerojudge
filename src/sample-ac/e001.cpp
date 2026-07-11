#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    while (cin >> n >> q) {
        vector<int> h(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> h[i];
        }
        
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        
        sort(order.begin(), order.end(), [&](int a, int b) {
            return h[a] < h[b];
        });
        
        vector<int> L(n + 1, 0), R(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                L[order[i]] = order[i - 1];
            }
            if (i < n - 1) {
                R[order[i]] = order[i + 1];
            }
        }
        
        for (int i = 0; i < q; ++i) {
            int x;
            cin >> x;
            cout << L[x] << " " << R[x] << "\n";
            
            R[L[x]] = R[x];
            L[R[x]] = L[x];
        }
    }
    
    return 0;
}
