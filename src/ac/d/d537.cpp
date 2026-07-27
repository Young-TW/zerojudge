#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        // coordinates of the three primary colours: 0 = R, 1 = Y, 2 = B
        int xs[3] = {-1, -1, -1};
        int ys[3] = {-1, -1, -1};
        for (int i = 0; i < 3; ++i) {
            char c; int x, y;
            cin >> c >> x >> y;
            if (c == 'R') { xs[0] = x; ys[0] = y; }
            else if (c == 'Y') { xs[1] = x; ys[1] = y; }
            else if (c == 'B') { xs[2] = x; ys[2] = y; }
        }
        char target; cin >> target;

        // mask -> colour character
        char col[8];
        for (int i = 0; i < 8; ++i) col[i] = '?';
        col[1] = 'R';
        col[2] = 'Y';
        col[4] = 'B';
        col[3] = 'O'; // R+Y
        col[5] = 'P'; // R+B
        col[6] = 'G'; // Y+B
        col[7] = 'D'; // R+Y+B

        // maximal time needed until every source covers the whole board
        int tmax = 0;
        for (int i = 0; i < 3; ++i) {
            int farX = max(xs[i], N - 1 - xs[i]);
            int farY = max(ys[i], N - 1 - ys[i]);
            tmax = max(tmax, max(farX, farY));
        }

        int answer = 0;
        for (int t = 0; t <= tmax; ++t) {
            int cnt = 0;
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    int mask = 0;
                    if (max(abs(x - xs[0]), abs(y - ys[0])) <= t) mask |= 1;
                    if (max(abs(x - xs[1]), abs(y - ys[1])) <= t) mask |= 2;
                    if (max(abs(x - xs[2]), abs(y - ys[2])) <= t) mask |= 4;
                    if (col[mask] == target) ++cnt;
                }
            }
            if (cnt > answer) answer = cnt;
        }
        cout << answer << '\n';
    }
    return 0;
}
