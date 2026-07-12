#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

inline long long pw(long long a, long long b) {
    long long r = 1; a %= MOD;
    if(a == 0) return 0;
    while(b) {
        if(b&1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while(cin >> N >> M) {
        long long ans = 0;
        long long MN = pw(M, N);
        long long MN1 = MN * M % MOD;
        long long nn1 = (long long)N * (N + 1) / 2 % MOD;
        
        vector<long long> inv(M > 1 ? M : 2);
        if(M > 1) {
            inv[1] = 1;
            for(int i = 2; i < M; ++i) {
                inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
            }
        }
        
        for(int k = 1; k <= M; ++k) {
            if(k == M) {
                ans = (ans + MN * nn1) % MOD;
            } else {
                long long k2 = (long long)k * k % MOD;
                long long term1 = pw(k, N + 2);
                long long term2 = (N + 1LL) * MN % MOD * k2 % MOD;
                long long term3 = (1LL * N) * MN1 % MOD * k % MOD;
                long long num = ((term1 - term2 + term3) % MOD + MOD) % MOD;
                long long diff = M - k;
                long long inv_diff = inv[diff];
                long long inv_den = inv_diff * inv_diff % MOD;
                ans = (ans + num * inv_den) % MOD;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
