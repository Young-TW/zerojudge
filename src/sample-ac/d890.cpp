#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k) {
        vector<int> gifts(n);
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> gifts[i];
            sum += gifts[i];
        }
        
        bitset<50005> dp;
        dp[0] = 1;
        for (int i = 0; i < n; ++i) {
            dp |= (dp << gifts[i]);
        }
        
        int half = sum / 2;
        for (int i = half; i >= 0; --i) {
            if (dp[i]) {
                cout << i << " " << sum - i << "\n";
                break;
            }
        }
    }
    
    return 0;
}
