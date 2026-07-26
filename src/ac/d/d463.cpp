#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long N;
    const unsigned long long U = 2642245ULL;   // safe upper bound
    
    while (cin >> N) {
        unsigned long long lo = 0, hi = U, ans = 0;
        while (lo <= hi) {
            unsigned long long mid = lo + (hi - lo) / 2;
            __int128 cube = (__int128)mid * mid * mid;
            if (cube == ( __int128)N) {
                ans = mid;
                break;
            } else if (cube < ( __int128)N) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
