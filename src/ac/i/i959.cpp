#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            int max_val;
            cin >> max_val;
            int ans = -2000000000;
            for (int i = 1; i < n; ++i) {
                int x;
                cin >> x;
                ans = max(ans, max_val - x);
                max_val = max(max_val, x);
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
