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
        
        vector<int> dp;
        for (int i = 0; i < n; ++i) {
            auto it = lower_bound(dp.begin(), dp.end(), a[i]);
            if (it == dp.end()) {
                dp.push_back(a[i]);
            } else {
                *it = a[i];
            }
        }
        
        cout << dp.size() << "\n";
    }
    
    return 0;
}
