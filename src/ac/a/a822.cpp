#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, rs, cs;
    while (cin >> N >> rs >> cs) {
        const int SZ = N * N;
        vector<int> board(SZ, 0);          // number written in each cell
        int cur = rs * N + cs;             // current index (row‑major)

        for (int t = 1; t <= SZ; ++t) {
            board[cur] = t;
            if (t == SZ) break;
            int step = t;
            int nxt = (cur + step) % SZ;
            while (board[nxt] != 0) {
                nxt = (nxt + 1) % SZ;
            }
            cur = nxt;
        }

        // ----- find sinks -------------------------------------------------
        vector<int> sink(SZ, -1);          // -1 = unknown, otherwise index of sink

        auto getSink = [&](int start) {
            vector<int> path;
            int p = start;
            while (sink[p] == -1) {
                int r = p / N;
                int c = p % N;
                int curVal = board[p];
                int bestPos = -1;
                int bestVal = curVal;

                // up
                if (r > 0) {
                    int q = (r - 1) * N + c;
                    if (board[q] < bestVal) {
                        bestVal = board[q];
                        bestPos = q;
                    }
                }
                // down
                if (r + 1 < N) {
                    int q = (r + 1) * N + c;
                    if (board[q] < bestVal) {
                        bestVal = board[q];
                        bestPos = q;
                    }
                }
                // left
                if (c > 0) {
                    int q = r * N + (c - 1);
                    if (board[q] < bestVal) {
                        bestVal = board[q];
                        bestPos = q;
                    }
                }
                // right
                if (c + 1 < N) {
                    int q = r * N + (c + 1);
                    if (board[q] < bestVal) {
                        bestVal = board[q];
                        bestPos = q;
                    }
                }

                if (bestPos == -1) {          // p is a sink
                    sink[p] = p;
                    break;
                }
                path.push_back(p);
                p = bestPos;
            }
            int finalSink = sink[p];
            for (int v : path) sink[v] = finalSink;
            return finalSink;
        };

        vector<int> cnt(SZ, 0);
        for (int i = 0; i < SZ; ++i) {
            int s = getSink(i);
            ++cnt[s];
        }

        int totalStops = 0, maxBalls = 0;
        for (int i = 0; i < SZ; ++i) {
            if (cnt[i] > 0) {
                ++totalStops;
                if (cnt[i] > maxBalls) maxBalls = cnt[i];
            }
        }
        cout << totalStops << ' ' << maxBalls << '\n';
    }
    return 0;
}
