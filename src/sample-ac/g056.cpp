#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long c0, t;
    const int MOD = 998244353;
    
    while (cin >> N >> c0 >> t) {
        vector<int> c(N);
        c[0] = c0 % MOD;
        for (int i = 1; i < N; ++i) {
            c[i] = (10007LL * c[i - 1] + t) % MOD;
        }
        
        int K = 0;
        while ((1 << K) < N) ++K;
        
        for (int i = 0; i < K; ++i) {
            int bit = 1 << i;
            for (int mask = 0; mask < N; ++mask) {
                if (mask & bit) {
                    int val = c[mask] - c[mask ^ bit];
                    if (val < 0) val += MOD;
                    c[mask] = val;
                }
            }
        }
        
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            ans ^= c[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
