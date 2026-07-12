#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244853;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, k;
    while (cin >> N >> k) {
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        sort(A.begin(), A.end());
        
        vector<int> counts;
        for (int i = 0; i < N; ) {
            int j = i;
            while (j < N && A[j] == A[i]) {
                ++j;
            }
            counts.push_back(j - i);
            i = j;
        }
        
        vector<long long> dp(k + 1, 0);
        dp[0] = 1;
        
        for (int c : counts) {
            for (int j = k; j >= 1; --j) {
                dp[j] = (dp[j] + dp[j - 1] * c) % MOD;
            }
        }
        
        cout << dp[k] << "\n";
    }
    
    return 0;
}
