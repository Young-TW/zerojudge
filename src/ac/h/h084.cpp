#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k) {
        vector<int> h(n);
        for (int i = 0; i < n; i++) cin >> h[i];
        vector<int> w(k);
        for (int i = 0; i < k; i++) cin >> w[i];
        
        int max_h = *max_element(h.begin(), h.end());
        
        auto check = [&](int x) -> bool {
            int pos = 0;
            for (int i = 0; i < k; i++) {
                int need = w[i];
                int cnt = 0;
                while (pos < n && cnt < need) {
                    if (h[pos] >= x) {
                        cnt++;
                    } else {
                        cnt = 0;
                    }
                    pos++;
                }
                if (cnt < need) return false;
            }
            return true;
        };
        
        int lo = 1, hi = max_h, ans = 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
