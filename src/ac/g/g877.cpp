#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        
        long long ans;
        if (n % 2 == 0) {
            // No collisions possible when n is even
            ans = ((k - 1) % n) + 1;
        } else {
            // n is odd: collisions occur periodically
            // f(t) = (2t + s(t)) mod n cycles through 2, 4, ..., n-1, 2, ...
            // Period = (n-1)/2, one skip per period
            long long p = (n - 1) / 2;
            long long s = (k - 1) / p;  // number of skips up to minute k
            ans = ((k - 1 + s) % n) + 1;
        }
        cout << ans << "\n";
    }
    return 0;
}
