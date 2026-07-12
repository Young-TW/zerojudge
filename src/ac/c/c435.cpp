#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        int max_val = a[0];
        int ans = -2000000000;
        
        for (int j = 1; j < n; ++j) {
            ans = max(ans, max_val - a[j]);
            max_val = max(max_val, a[j]);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
