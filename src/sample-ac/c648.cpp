#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int W, L;
        cin >> W >> L;
        vector<int> H(W); // 1-indexed: platforms 1 .. W-1
        for (int i = 1; i < W; ++i) {
            cin >> H[i];
        }
        
        vector<long long> pref(W);
        for (int i = 1; i < W; ++i) {
            pref[i] = pref[i-1] + H[i];
        }
        
        long long ans = LLONG_MAX;
        // sliding window of length L over platforms 1..W-1
        for (int i = 1; i + L - 1 < W; ++i) {
            long long sum = pref[i + L - 1] - pref[i - 1];
            if (sum < ans) ans = sum;
        }
        
        cout << ans << '\n';
    }
    return 0;
}
