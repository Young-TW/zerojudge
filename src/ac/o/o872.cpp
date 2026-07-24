#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    if (cin >> N) {
        const long long MOD = 1000000007;
        long long ans = ((N % MOD) * (N % MOD) % MOD - (N % MOD) + 1 + MOD) % MOD;
        cout << ans << "\n";
    }

    return 0;
}
