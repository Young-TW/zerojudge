#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        
        if (m > n) {
            cout << "Impossible\n";
            continue;
        }
        
        vector<int> window_sum(201, 0);
        bool found = false;
        
        for (int i = 0; i < n; ++i) {
            int height = h[i];
            int start_L = max(0, height - k);
            int end_L = min(200, height);
            
            for (int L = start_L; L <= end_L; ++L) {
                window_sum[L]++;
                if (window_sum[L] >= m) {
                    cout << i + 1 << "\n";
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        
        if (!found) {
            cout << "Impossible\n";
        }
    }
    
    return 0;
}
