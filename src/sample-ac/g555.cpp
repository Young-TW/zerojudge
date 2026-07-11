#include <iostream>

using namespace std;

const int MOD = 998244353;
const int MAXN = 200005;

int fib[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i < MAXN; ++i) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }
    
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            int ans = (fib[n + 2] - 1 + MOD) % MOD;
            cout << ans << "\n";
        }
    }
    
    return 0;
}
