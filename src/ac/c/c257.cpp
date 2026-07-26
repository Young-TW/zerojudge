#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

const int64_t MOD = 1000000009LL;
const int MAX_SUM = 1000000;          // 1000 * 1000

// fast exponentiation modulo MOD
int64_t modPow(int64_t a, int64_t e) {
    int64_t r = 1;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // factorials
    static vector<int64_t> fact(MAX_SUM + 1);
    fact[0] = 1;
    for (int i = 1; i <= MAX_SUM; ++i)
        fact[i] = fact[i - 1] * i % MOD;

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        int n;
        cin >> n;
        vector<int> p(n);
        int maxRow = 0;
        int64_t total = 0;
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
            if (p[i] > maxRow) maxRow = p[i];
            total += p[i];
        }

        // column heights
        vector<int> colHeight(maxRow, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < p[i]; ++j) {
                ++colHeight[j];
            }
        }

        int64_t prod = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < p[i]; ++j) {
                int right = p[i] - j - 1;
                int down  = colHeight[j] - i - 1;
                int hook = right + down + 1;
                prod = prod * hook % MOD;
            }
        }

        int64_t ans = fact[total] * modPow(prod, MOD - 2) % MOD;
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
