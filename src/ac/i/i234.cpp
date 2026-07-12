#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXM = 1 << 20;
const int MOD = 998244353;

int cnt[MAXM];
int g[MAXM];
int f[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        
        vector<int> pow2(n + 1);
        pow2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }
        
        for (int mask = 0; mask < MAXM; ++mask) {
            g[mask] = cnt[mask];
        }
        for (int i = 0; i < 20; ++i) {
            for (int mask = 0; mask < MAXM; ++mask) {
                if (mask & (1 << i)) {
                    g[mask] += g[mask ^ (1 << i)];
                }
            }
        }
        for (int mask = 0; mask < MAXM; ++mask) {
            f[mask] = pow2[g[mask]];
        }
        for (int i = 0; i < 20; ++i) {
            for (int mask = 0; mask < MAXM; ++mask) {
                if (mask & (1 << i)) {
                    f[mask] -= f[mask ^ (1 << i)];
                    if (f[mask] < 0) f[mask] += MOD;
                }
            }
        }
        cout << f[MAXM - 1] << "\n";
    }
    return 0;
}
