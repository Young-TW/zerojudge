#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> p(n), c(n), pos(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i] >> c[i];
            pos[p[i]] = i;
        }
        
        vector<int> diff(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int x = pos[i];
            int L = i - c[i] - x;
            int R = i + c[i] - x;
            
            L = (L % n + n) % n;
            R = (R % n + n) % n;
            
            if (L <= R) {
                diff[L]++;
                diff[R + 1]--;
            } else {
                diff[L]++;
                diff[0]++;
                diff[R + 1]--;
            }
        }
        
        int ans = 0;
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            cur += diff[i];
            if (cur > ans) {
                ans = cur;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
