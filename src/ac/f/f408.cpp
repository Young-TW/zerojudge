#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        
        sort(arr.begin(), arr.end(), [](int a, int b) {
            return abs(a) < abs(b);
        });
        
        int ans = 0;
        for (int i = 1; i < n; ++i) {
            if ((arr[i] > 0) != (arr[i - 1] > 0)) {
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
