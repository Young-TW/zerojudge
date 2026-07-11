#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N;
        cin >> N;
        
        int dp[31] = {0};
        for (int i = 0; i < N; ++i) {
            int P, W;
            cin >> P >> W;
            for (int w = 30; w >= W; --w) {
                if (dp[w - W] + P > dp[w]) {
                    dp[w] = dp[w - W] + P;
                }
            }
        }
        
        int G;
        cin >> G;
        long long ans = 0;
        for (int i = 0; i < G; ++i) {
            int MW;
            cin >> MW;
            ans += dp[MW];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
