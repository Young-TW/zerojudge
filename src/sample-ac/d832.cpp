#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    long long m;
    while (cin >> n >> m) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        vector<long long> L(n), R(n+1);
        long long cur = 0, mx = 0;
        for (int i = 0; i < n; i++) {
            cur = max(0LL, cur + a[i]);
            mx = max(mx, cur);
            L[i] = mx;
        }
        cur = 0; mx = 0;
        R[n] = 0;
        for (int i = n-1; i >= 0; i--) {
            cur = max(0LL, cur + a[i]);
            mx = max(mx, cur);
            R[i] = mx;
        }
        
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, L[i] + R[i+1]);
        }
        cout << ans << "\n";
    }
    return 0;
}
