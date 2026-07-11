#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<long long> diff(n + 2, 0);
        for (int i = 0; i < m; ++i) {
            int l, r, w;
            cin >> l >> r >> w;
            diff[l] += w;
            diff[r + 1] -= w;
        }
        
        vector<long long> C(n + 1, 0);
        long long cur = 0;
        for (int i = 1; i <= n; ++i) {
            cur += diff[i];
            C[i] = cur;
        }
        
        sort(C.begin() + 1, C.end());
        
        vector<int> t(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> t[i];
        }
        
        sort(t.begin() + 1, t.end(), greater<int>());
        
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += C[i] * t[i];
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
