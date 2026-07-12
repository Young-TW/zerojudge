#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    while (cin >> m >> n) {
        vector<long long> masks;
        masks.reserve(n);
        long long full_mask = (m == 0) ? 0 : ((1LL << m) - 1);
        
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            long long mask = 0;
            for (char c : s) {
                int idx;
                if (c >= 'A' && c <= 'Z') {
                    idx = c - 'A';
                } else {
                    idx = c - 'a' + 26;
                }
                if (idx < m) {
                    mask |= (1LL << idx);
                }
            }
            masks.push_back(mask);
        }
        
        sort(masks.begin(), masks.end());
        
        long long ans = 0;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && masks[j] == masks[i]) {
                j++;
            }
            long long count = j - i;
            long long mask = masks[i];
            long long comp = full_mask ^ mask;
            
            if (mask < comp) {
                auto it_low = lower_bound(masks.begin(), masks.end(), comp);
                auto it_up = upper_bound(masks.begin(), masks.end(), comp);
                ans += count * (it_up - it_low);
            }
            i = j;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
