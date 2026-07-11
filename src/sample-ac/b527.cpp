#include <iostream>
#include <bitset>

using namespace std;

const int MOD = 10007;
bitset<MOD> dp, dp_nonempty;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M;
    while (cin >> M) {
        if (M < 2) {
            for (int i = 0; i < M; ++i) {
                int x;
                cin >> x;
            }
            cout << "NO\n";
            continue;
        }
        int arr[25];
        int total_sum = 0;
        for (int i = 0; i < M; ++i) {
            cin >> arr[i];
            arr[i] %= MOD;
            total_sum = (total_sum + arr[i]) % MOD;
        }
        int target = (total_sum * 5004) % MOD;
        
        dp.reset();
        dp_nonempty.reset();
        dp[0] = 1;
        
        int start = (target == 0) ? 1 : 0;
        for (int i = start; i < M; ++i) {
            int x = arr[i];
            bitset<MOD> new_dp = (dp << x) | (dp >> (MOD - x));
            dp |= new_dp;
            dp_nonempty |= new_dp;
        }
        
        if (dp_nonempty[target]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
