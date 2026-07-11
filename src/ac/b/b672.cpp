#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        
        int current_max = 5;
        if (current_max >= n + 1) {
            cout << 0 << "\n";
            continue;
        }
        
        int ans = 0;
        int start = 1;
        
        while (current_max < n + 1) {
            int next_max = current_max;
            for (int j = start; j <= current_max; ++j) {
                next_max = max(next_max, j + a[j]);
            }
            ans++;
            start = current_max + 1;
            current_max = next_max;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
