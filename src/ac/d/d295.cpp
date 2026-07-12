#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long x[4], y[4];
    while (cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2] >> x[3] >> y[3]) {
        long long sx[4], sy[4];
        if (!(cin >> sx[0] >> sy[0] >> sx[1] >> sy[1] >> sx[2] >> sy[2] >> sx[3] >> sy[3])) {
            break;
        }

        long long min_x = *min_element(x, x + 4);
        long long max_x = *max_element(x, x + 4);
        long long min_y = *min_element(y, y + 4);
        long long max_y = *max_element(y, y + 4);

        long long W = max_x - min_x;
        long long H = max_y - min_y;

        long long min_sx = *min_element(sx, sx + 4);
        long long max_sx = *max_element(sx, sx + 4);
        long long min_sy = *min_element(sy, sy + 4);
        long long max_sy = *max_element(sy, sy + 4);

        long long L = min_sx - min_x;
        long long R = max_x - max_sx;
        long long D = min_sy - min_y;
        long long U = max_y - max_sy;

        long long total_x = W * (W + 1) / 2;
        long long total_y = H * (H + 1) / 2;
        long long total = total_x * total_y;

        long long Cx = total_x - L * (L + 1) / 2 - R * (R + 1) / 2;
        long long Cy = total_y - D * (D + 1) / 2 - U * (U + 1) / 2;
        
        long long Cin = (L + 1) * (R + 1) * (D + 1) * (U + 1);

        long long ans = total - Cx * Cy + Cin;
        cout << ans << "\n";
    }

    return 0;
}
