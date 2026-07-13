#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <tuple>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 1002; // 1000 + 2

static int bit[MAXN][MAXN];
int R, C;

inline void bit_update(int x, int y, int val) {
    for (int i = x; i <= R; i += i & -i) {
        for (int j = y; j <= C; j += j & -j) {
            bit[i][j] += val;
            if (bit[i][j] >= MOD) bit[i][j] -= MOD;
        }
    }
}

inline int bit_query(int x, int y) {
    long long res = 0;
    for (int i = x; i > 0; i -= i & -i) {
        for (int j = y; j > 0; j -= j & -j) {
            res += bit[i][j];
        }
    }
    return static_cast<int>(res % MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        cin >> R >> C;
        vector<tuple<int, int, int>> cells;
        cells.reserve(R * C);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                int val;
                cin >> val;
                cells.emplace_back(val, i, j);
            }
        }
        memset(bit, 0, sizeof(bit));
        
        sort(cells.begin(), cells.end(), [](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b);
        });
        
        long long ans = 0;
        for (size_t i = 0; i < cells.size(); ) {
            size_t j = i;
            int current_val = get<0>(cells[i]);
            vector<int> dp_vals;
            dp_vals.reserve(j - i + 1);
            while (j < cells.size() && get<0>(cells[j]) == current_val) {
                int x = get<1>(cells[j]) + 1;
                int y = get<2>(cells[j]) + 1;
                int sum = bit_query(x, y);
                int dp = (1 + sum) % MOD;
                dp_vals.push_back(dp);
                ans += dp;
                if (ans >= MOD) ans -= MOD;
                ++j;
            }
            size_t idx = 0;
            for (size_t k = i; k < j; ++k) {
                int x = get<1>(cells[k]) + 1;
                int y = get<2>(cells[k]) + 1;
                bit_update(x, y, dp_vals[idx++]);
            }
            i = j;
        }
        cout << ans % MOD << '\n';
    }
    return 0;
}
