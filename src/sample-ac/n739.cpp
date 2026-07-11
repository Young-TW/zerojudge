#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int W, H;
    while (cin >> W >> H) {
        int N;
        cin >> N;
        
        // 1D DP array for better cache locality: index = w * (H+1) + h
        vector<long long> dp((W + 1) * (H + 1), 0);
        auto idx = [&](int w, int h) { return w * (H + 1) + h; };
        
        for (int i = 0; i < N; ++i) {
            long long v;
            int w, h;
            cin >> v >> w >> h;
            if (w <= W && h <= H) dp[idx(w, h)] = max(dp[idx(w, h)], v);
            if (h <= W && w <= H) dp[idx(h, w)] = max(dp[idx(h, w)], v);
        }
        
        for (int w = 1; w <= W; ++w) {
            for (int h = 1; h <= H; ++h) {
                long long &res = dp[idx(w, h)];
                // vertical cuts (split width)
                for (int k = 1; k <= w / 2; ++k) {
                    res = max(res, dp[idx(k, h)] + dp[idx(w - k, h)]);
                }
                // horizontal cuts (split height)
                for (int k = 1; k <= h / 2; ++k) {
                    res = max(res, dp[idx(w, k)] + dp[idx(w, h - k)]);
                }
            }
        }
        
        cout << dp[idx(W, H)] << '\n';
    }
    return 0;
}
