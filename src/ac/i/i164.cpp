#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> T(n);
        for (int i = 0; i < n; ++i) {
            cin >> T[i];
        }
        
        vector<vector<int>> pos(100005);
        for (int i = 0; i < n; ++i) {
            int s;
            cin >> s;
            pos[s].push_back(i);
        }
        
        for (int i = 0; i < n; ++i) {
            int val = T[i];
            if (pos[val].empty()) {
                if (i > 0) cout << " ";
                cout << -1;
            } else {
                auto it = lower_bound(pos[val].begin(), pos[val].end(), i);
                int ans = n + 1;
                if (it != pos[val].end()) {
                    ans = min(ans, *it - i);
                }
                if (it != pos[val].begin()) {
                    auto prev_it = it - 1;
                    ans = min(ans, i - *prev_it);
                }
                if (i > 0) cout << " ";
                cout << ans;
            }
        }
        cout << "\n";
    }
    
    return 0;
}
