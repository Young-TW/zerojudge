#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Operation {
    int r, c, t, x;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, N;
    while (cin >> H >> W >> N) {
        vector<Operation> ops(N);
        for (int i = 0; i < N; ++i) {
            cin >> ops[i].r >> ops[i].c >> ops[i].t >> ops[i].x;
        }

        vector<vector<int>> grid(H, vector<int>(W, 0));

        for (const auto& op : ops) {
            int r = op.r;
            int c = op.c;
            int t = op.t;
            int x = op.x;

            int start_r = max(0, r - t);
            int end_r = min(H - 1, r + t);
            int start_c = max(0, c - t);
            int end_c = min(W - 1, c + t);

            for (int i = start_r; i <= end_r; ++i) {
                for (int j = start_c; j <= end_c; ++j) {
                    int dist = abs(i - r) + abs(j - c);
                    if (dist <= t) {
                        grid[i][j] += x;
                    }
                }
            }
        }

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (j != 0) cout << " ";
                cout << grid[i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}
