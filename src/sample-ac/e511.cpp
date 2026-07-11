#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            int min_val = 100;
            int max_val = 0;
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                min_val = min(min_val, x);
                max_val = max(max_val, x);
            }
            cout << (max_val - min_val) * 2 << "\n";
        }
    }
    
    return 0;
}
