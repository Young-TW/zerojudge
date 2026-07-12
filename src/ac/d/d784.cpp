#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            int max_sum = INT_MIN;
            int current_sum = 0;
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                current_sum = max(x, current_sum + x);
                max_sum = max(max_sum, current_sum);
            }
            cout << max_sum << "\n";
        }
    }
    
    return 0;
}
