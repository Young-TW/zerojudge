#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> t(n);
        for (int i = 0; i < n; ++i) {
            cin >> t[i];
        }
        
        vector<int> S(m), E(m);
        for (int i = 0; i < m; ++i) {
            cin >> S[i] >> E[i];
        }
        
        sort(S.begin(), S.end());
        sort(E.begin(), E.end());
        
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int val = t[i];
            long long cnt_S = upper_bound(S.begin(), S.end(), val) - S.begin();
            long long cnt_E = lower_bound(E.begin(), E.end(), val) - E.begin();
            ans += (cnt_S - cnt_E);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
