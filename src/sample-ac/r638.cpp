#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<long long> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        long long p, q;
        cin >> p >> q;
        
        if (q == 0) { p = 1; q = 1; }
        
        int N = n;
        // decay[k*N + i] = f^k(v[i]), where f(x) = floor(x * p / q)
        vector<long long> decay((size_t)N * N);
        for (int i = 0; i < N; i++) {
            decay[i] = v[i];
        }
        for (int k = 1; k < N; k++) {
            long long* prev = &decay[(size_t)(k - 1) * N];
            long long* cur = &decay[(size_t)k * N];
            for (int i = 0; i < N; i++) {
                cur[i] = (prev[i] * p) / q;
            }
        }
        
        // dp[l] = optimal (first - second) for subarray [l, l+len-1]
        // For subarray of length len, decay count k = N - len
        vector<long long> dp(N), ndp(N);
        // len = 1, k = N-1
        long long* baseRow = &decay[(size_t)(N - 1) * N];
        for (int l = 0; l < N; l++) {
            dp[l] = baseRow[l];
        }
        
        for (int len = 2; len <= N; len++) {
            int k = N - len;
            long long* row = &decay[(size_t)k * N];
            for (int l = 0; l + len - 1 < N; l++) {
                int r = l + len - 1;
                long long takeLeft = row[l] - dp[l + 1];
                long long takeRight = row[r] - dp[l];
                ndp[l] = max(takeLeft, takeRight);
            }
            dp.swap(ndp);
        }
        
        cout << dp[0] << "\n";
    }
    
    return 0;
}
