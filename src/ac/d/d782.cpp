#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long S;
    long long mod = 100000007;
    
    while (cin >> S && S != 0) {
        bool found = false;
        for (long long x = 1; 6 * x * x < S; ++x) {
            if (S % x == 0) {
                long long val = S / x - 6 * x;
                if (val % 7 == 0) {
                    long long y = val / 7;
                    long long ans = (2 * (y % mod) * (y % mod)) % mod;
                    cout << "Possible Missing Soldiers = " << ans << "\n";
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "No Solution Possible\n";
        }
        cout << "\n";
    }
    
    return 0;
}
