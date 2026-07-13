#include <iostream>
#include <string>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        long long dp = 1;
        long long lastA = 0, lastB = 0;
        
        for (char c : s) {
            long long prevDp = dp;
            if (c == 'A') {
                dp = (prevDp * 2 % MOD - lastA + MOD) % MOD;
                lastA = prevDp;
            } else {
                dp = (prevDp * 2 % MOD - lastB + MOD) % MOD;
                lastB = prevDp;
            }
        }
        
        cout << (dp - 1 + MOD) % MOD << "\n";
    }
    
    return 0;
}
