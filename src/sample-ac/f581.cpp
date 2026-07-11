#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];
        
        vector<long long> prefix(2 * n + 1);
        prefix[0] = 0;
        for (int i = 0; i < 2 * n; ++i) {
            prefix[i+1] = prefix[i] + p[i % n];
        }
        
        int s = 0;
        for (int i = 0; i < m; ++i) {
            int q;
            cin >> q;
            long long target = prefix[s] + q;
            int idx = lower_bound(prefix.begin() + s + 1, prefix.begin() + s + n + 1, target) - prefix.begin();
            int t = idx - 1;
            s = (t + 1) % n;
        }
        cout << s << "\n";
    }
    return 0;
}
