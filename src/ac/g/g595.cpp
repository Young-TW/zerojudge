#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        
        int total_cost = 0;
        for (int i = 0; i < n; ++i) {
            if (h[i] == 0) {
                if (i == 0) {
                    total_cost += h[1];
                } else if (i == n - 1) {
                    total_cost += h[n - 2];
                } else {
                    total_cost += min(h[i - 1], h[i + 1]);
                }
            }
        }
        
        cout << total_cost << "\n";
    }
    
    return 0;
}
