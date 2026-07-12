#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long L;
    while (cin >> L) {
        if (L <= 0) continue;
        
        // Find minimal n such that floor((n+1)^2/4) >= L
        // Equivalent to (n+1)^2 >= 4L
        long long val = 4LL * L;
        long long t = sqrt((long double)val);
        while ((t + 1) * (t + 1) <= val) ++t;
        while (t * t > val) --t;
        long long n = (t * t == val) ? t - 1 : t;
        
        long long rem = L;
        // First step is always 1
        cout << 1;
        rem -= 1;
        long long prev = 1;
        
        for (long long i = 2; i <= n; ++i) {
            long long r = n - i + 1; // remaining steps including current
            long long chosen = -1;
            // Try candidates in increasing order: prev-1, prev, prev+1 (but >=1)
            for (long long cand = max(1LL, prev - 1); cand <= prev + 1; ++cand) {
                long long mn, mx;
                if (r < cand) {
                    mn = LLONG_MAX; // impossible
                } else {
                    mn = cand * (cand - 1) / 2 + r;
                }
                long long p = (r + cand) / 2;
                mx = p * (r + cand - p) - (cand - 1) * cand / 2;
                
                if (mn <= rem && rem <= mx) {
                    chosen = cand;
                    break;
                }
            }
            cout << ' ' << chosen;
            rem -= chosen;
            prev = chosen;
        }
        cout << '\n';
    }
    return 0;
}
