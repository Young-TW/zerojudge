#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int j = i; j < n; ++j) {
                sum += a[j];
                if (sum <= k) {
                    if (sum > ans) {
                        ans = sum;
                    }
                } else {
                    break; // Optimization: since a[j] > 0, sum will only increase
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
