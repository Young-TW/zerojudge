#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const long long MOD = 100000007LL;
    long long N;
    // the official input contains a single integer, but reading until EOF also works
    while (cin >> N) {
        long long cur[2][3] = {};   // cur[usedLeave][runR]
        long long nxt[2][3] = {};
        cur[0][0] = 1;               // empty prefix
        
        for (long long i = 0; i < N; ++i) {
            // clear nxt
            for (int a = 0; a < 2; ++a)
                for (int r = 0; r < 3; ++r)
                    nxt[a][r] = 0;
            
            for (int a = 0; a < 2; ++a) {
                for (int r = 0; r < 3; ++r) {
                    long long val = cur[a][r];
                    if (!val) continue;
                    
                    // add P : resets runR
                    nxt[a][0] += val;
                    if (nxt[a][0] >= MOD) nxt[a][0] -= MOD;
                    
                    // add R : only if we would not create RRR
                    if (r < 2) {
                        nxt[a][r + 1] += val;
                        if (nxt[a][r + 1] >= MOD) nxt[a][r + 1] -= MOD;
                    }
                    
                    // add L : only if we have not used a leave yet
                    if (a == 0) {
                        nxt[1][0] += val;
                        if (nxt[1][0] >= MOD) nxt[1][0] -= MOD;
                    }
                }
            }
            // move nxt -> cur
            for (int a = 0; a < 2; ++a)
                for (int r = 0; r < 3; ++r)
                    cur[a][r] = nxt[a][r];
        }
        
        long long ans = 0;
        for (int a = 0; a < 2; ++a)
            for (int r = 0; r < 3; ++r) {
                ans += cur[a][r];
                if (ans >= MOD) ans -= MOD;
            }
        cout << ans % MOD << '\n';
    }
    return 0;
}
