#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    for (int cas = 1; cas <= t; ++cas) {
        int n, p, q;
        cin >> n >> p >> q;
        
        int sz = n * n;
        vector<int> pos(sz + 1, 0);
        
        for (int i = 1; i <= p + 1; ++i) {
            int x;
            cin >> x;
            pos[x] = i;
        }
        
        vector<int> v;
        for (int i = 0; i < q + 1; ++i) {
            int x;
            cin >> x;
            if (pos[x] != 0) {
                v.push_back(pos[x]);
            }
        }
        
        vector<int> dp;
        for (int x : v) {
            auto it = lower_bound(dp.begin(), dp.end(), x);
            if (it == dp.end()) {
                dp.push_back(x);
            } else {
                *it = x;
            }
        }
        
        cout << "Case " << cas << ": " << dp.size() << "\n";
    }
    
    return 0;
}
