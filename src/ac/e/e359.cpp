#include <iostream>
#include <string>

using namespace std;

const long long MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        string s;
        if (n == 1) {
            cin >> s;
            bool neg = false;
            size_t start = 0;
            if (!s.empty() && s[0] == '-') {
                neg = true;
                start = 1;
            } else if (!s.empty() && s[0] == '+') {
                start = 1;
            }
            
            long long ans = 0;
            for (size_t i = start; i < s.size(); ++i) {
                if (s[i] >= '0' && s[i] <= '9') {
                    ans = (ans * 10 + (s[i] - '0')) % MOD;
                }
            }
            
            if (neg) {
                ans = (MOD - ans) % MOD;
            }
            cout << ans << "\n";
        } else {
            for (long long i = 0; i < n; ++i) {
                cin >> s;
            }
            cout << 0 << "\n";
        }
    }
    
    return 0;
}
