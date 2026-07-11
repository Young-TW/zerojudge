#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, k;
    while (cin >> n >> k) {
        long long ans = 0;
        long long m = min(n, k);
        
        long long L = 1;
        while (L <= m) {
            long long q = k / L;
            long long R = min(m, k / q);
            long long len = R - L + 1;
            long long sum_i = (L + R) * len / 2;
            ans += q * sum_i;
            L = R + 1;
        }
        
        ans = m * k - ans;
        
        if (n > k) {
            ans += (n - k) * k;
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
