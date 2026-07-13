#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int i, a;
    while (cin >> i >> a && (i || a)) {
        vector<int> req_mask(i, 0);
        vector<int> forb_mask(i, 0);

        for (int k = 0; k < a; ++k) {
            int x, y;
            cin >> x >> y;
            x--; // 0-indexed
            if (y > 0) {
                y--;
                req_mask[x] |= (1 << y);
            } else {
                y = -y;
                y--;
                forb_mask[x] |= (1 << y);
            }
        }

        int size = 1 << i;
        vector<int> R(size, 0);
        vector<int> F(size, 0);
        int ans = 0;

        for (int mask = 1; mask < size; ++mask) {
            int lowbit = mask & (-mask);
            int k = __builtin_ctz(lowbit);
            int sub = mask ^ lowbit;
            
            R[mask] = R[sub] | req_mask[k];
            F[mask] = F[sub] | forb_mask[k];

            if ((mask & R[mask]) == R[mask] && (mask & F[mask]) == 0) {
                ans = max(ans, __builtin_popcount(mask));
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
