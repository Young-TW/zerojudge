#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MAXN = 101;
    bool dp[MAXN][MAXN][MAXN];
    memset(dp, false, sizeof(dp));

    bool has_false_x[MAXN][MAXN];
    bool has_false_y[MAXN][MAXN];
    bool has_false_z[MAXN][MAXN];
    bool has_false_xy[MAXN][201];
    bool has_false_xz[MAXN][201];
    bool has_false_yz[MAXN][201];
    bool has_false_xyz[201][201];

    memset(has_false_x, false, sizeof(has_false_x));
    memset(has_false_y, false, sizeof(has_false_y));
    memset(has_false_z, false, sizeof(has_false_z));
    memset(has_false_xy, false, sizeof(has_false_xy));
    memset(has_false_xz, false, sizeof(has_false_xz));
    memset(has_false_yz, false, sizeof(has_false_yz));
    memset(has_false_xyz, false, sizeof(has_false_xyz));

    for (int x = 0; x < MAXN; ++x) {
        for (int y = 0; y < MAXN; ++y) {
            for (int z = 0; z < MAXN; ++z) {
                if (x == 0 && y == 0 && z == 0) {
                    dp[x][y][z] = false;
                } else {
                    bool is_w = false;
                    if (x > 0 && has_false_x[y][z]) is_w = true;
                    if (y > 0 && has_false_y[x][z]) is_w = true;
                    if (z > 0 && has_false_z[x][y]) is_w = true;
                    if (x > 0 && y > 0 && has_false_xy[z][x - y + 100]) is_w = true;
                    if (x > 0 && z > 0 && has_false_xz[y][x - z + 100]) is_w = true;
                    if (y > 0 && z > 0 && has_false_yz[x][y - z + 100]) is_w = true;
                    if (x > 0 && y > 0 && z > 0 && has_false_xyz[x - y + 100][x - z + 100]) is_w = true;
                    dp[x][y][z] = is_w;
                }

                if (!dp[x][y][z]) {
                    has_false_x[y][z] = true;
                    has_false_y[x][z] = true;
                    has_false_z[x][y] = true;
                    has_false_xy[z][x - y + 100] = true;
                    has_false_xz[y][x - z + 100] = true;
                    has_false_yz[x][y - z + 100] = true;
                    has_false_xyz[x - y + 100][x - z + 100] = true;
                }
            }
        }
    }

    int x, y, z;
    while (cin >> x) {
        if (x == 0) break;
        cin >> y >> z;
        if (dp[x][y][z]) {
            cout << "w\n";
        } else {
            cout << "l\n";
        }
    }

    return 0;
}
