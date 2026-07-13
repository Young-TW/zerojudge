#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sum += a[i];
        }
        
        if (sum % 2 != 0) {
            cout << 0 << "\n";
            continue;
        }
        
        long long target = sum / 2;
        vector<char> dp(target + 1, 0);
        dp[0] = 1;
        for (int x : a) {
            for (long long s = target; s >= x; s--) {
                if (dp[s - x]) dp[s] = 1;
            }
        }
        
        cout << (dp[target] ? 1 : 0) << "\n";
    }
    
    return 0;
}
