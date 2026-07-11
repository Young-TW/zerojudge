#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<int> W(n);
            for (int i = 0; i < n; ++i) {
                cin >> W[i];
            }
            
            vector<int> LIS(n, 1);
            vector<int> LDS(n, 1);
            int ans = 0;
            
            for (int i = n - 1; i >= 0; --i) {
                for (int j = i + 1; j < n; ++j) {
                    if (W[j] > W[i]) {
                        LIS[i] = max(LIS[i], LIS[j] + 1);
                    } else if (W[j] < W[i]) {
                        LDS[i] = max(LDS[i], LDS[j] + 1);
                    }
                }
                ans = max(ans, LIS[i] + LDS[i] - 1);
            }
            
            cout << ans << "\n";
        }
    }
    return 0;
}
