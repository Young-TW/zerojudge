#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int64 H, W, N, M;
        cin >> H >> W >> N >> M;

        // single row
        if (H == 1) {
            if (M <= 2 || M >= W - 1) {
                cout << -1 << '\n';
            } else {
                cout << 2 << '\n';
            }
            continue;
        }
        // single column
        if (W == 1) {
            if (N <= 2 || N >= H - 1) {
                cout << -1 << '\n';
            } else {
                cout << 2 << '\n';
            }
            continue;
        }
        // two rows or two columns
        if (H == 2 || W == 2) {
            cout << -1 << '\n';
            continue;
        }

        // H >= 3 && W >= 3
        int64 d1 = (N - 1) + (M - 1);          // to (1,1)
        int64 d2 = (N - 1) + (W - M);          // to (1,W)
        int64 d3 = (H - N) + (M - 1);          // to (H,1)
        int64 d4 = (H - N) + (W - M);          // to (H,W)
        int64 D = max( max(d1, d2), max(d3, d4) );
        cout << (2 * D) << '\n';
    }
    return 0;
}
