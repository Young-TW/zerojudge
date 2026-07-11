#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

bool obs[302][302][302];
unsigned short dp[2][302][302];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c;
    while (cin >> a >> b >> c) {
        int n;
        cin >> n;
        vector<tuple<int, int, int>> obstacles(n);
        for (int i = 0; i < n; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            obs[z][y][x] = true;
            obstacles[i] = make_tuple(x, y, z);
        }

        long long ans = 0;
        for (int z = 1; z <= c; ++z) {
            int cur = z % 2;
            int prev = 1 - cur;
            for (int y = 1; y <= b; ++y) {
                for (int x = 1; x <= a; ++x) {
                    if (obs[z][y][x]) {
                        dp[cur][y][x] = 0;
                    } else {
                        unsigned short m = dp[prev][y][x];
                        if (dp[cur][y-1][x] < m) m = dp[cur][y-1][x];
                        if (dp[cur][y][x-1] < m) m = dp[cur][y][x-1];
                        if (dp[prev][y-1][x] < m) m = dp[prev][y-1][x];
                        if (dp[prev][y][x-1] < m) m = dp[prev][y][x-1];
                        if (dp[cur][y-1][x-1] < m) m = dp[cur][y-1][x-1];
                        if (dp[prev][y-1][x-1] < m) m = dp[prev][y-1][x-1];
                        dp[cur][y][x] = m + 1;
                        ans += m + 1;
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            int x = get<0>(obstacles[i]);
            int y = get<1>(obstacles[i]);
            int z = get<2>(obstacles[i]);
            obs[z][y][x] = false;
        }

        cout << ans << "\n";
    }
    return 0;
}
