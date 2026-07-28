#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        vector<long long> h(n), w(n);
        for (long long i = 0; i < n; ++i) cin >> h[i];
        for (long long i = 0; i < n; ++i) cin >> w[i];
        
        long long ans_h = h[0], ans_w = w[0];
        __int128 best = (__int128)h[0] * (__int128)w[0];
        
        for (long long i = 1; i < n; ++i) {
            __int128 cur = (__int128)h[i] * (__int128)w[i];
            if (cur < best) {
                best = cur;
                ans_h = h[i];
                ans_w = w[i];
            }
        }
        cout << ans_h << ' ' << ans_w << '\n';
    }
    return 0;
}
