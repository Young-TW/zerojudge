#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<unsigned long long> cols(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                char c;
                cin >> c;
                while (c != '0' && c != '1') {
                    cin >> c;
                }
                if (c == '1') {
                    cols[j] |= (1ULL << i);
                }
            }
        }
        
        int ans = 0;
        unsigned long long limit = (1ULL << n);
        for (unsigned long long mask = 0; mask < limit; ++mask) {
            int current_ans = 0;
            for (int j = 0; j < n; ++j) {
                unsigned long long col_val = cols[j] ^ mask;
                int ones = __builtin_popcountll(col_val);
                current_ans += max(ones, n - ones);
            }
            if (current_ans > ans) {
                ans = current_ans;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
