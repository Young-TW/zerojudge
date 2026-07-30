#include <bits/stdc++.h>
using namespace std;

struct State {
    int o, rs, cs;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int X;
    if (!(cin >> X)) return 0;
    const string msgSwap = "DD thanks Honglin for his great kindness, DD will never forget it.";
    const string msgFail = "Uh-oh, DD can't sit with Badspeed.";
    while (X--) {
        int M1, N1, M2, N2;
        cin >> M1 >> N1 >> M2 >> N2;
        vector<vector<int>> A(M1, vector<int>(N1));
        for (int i = 0; i < M1; ++i)
            for (int j = 0; j < N1; ++j) cin >> A[i][j];
        vector<vector<int>> B(M2, vector<int>(N2));
        for (int i = 0; i < M2; ++i)
            for (int j = 0; j < N2; ++j) cin >> B[i][j];

        // sizes for the four orientations
        int rows[4], cols[4];
        rows[0] = M1; cols[0] = N1;
        rows[1] = N1; cols[1] = M1;
        rows[2] = M1; cols[2] = N1;
        rows[3] = N1; cols[3] = M1;

        // visited distances
        vector<vector<vector<int>>> dist(4);
        for (int o = 0; o < 4; ++o)
            dist[o].assign(rows[o], vector<int>(cols[o], -1));

        queue<State> q;
        dist[0][0][0] = 0;
        q.push({0,0,0});

        while (!q.empty()) {
            State cur = q.front(); q.pop();
            int d = dist[cur.o][cur.rs][cur.cs];
            // up
            {
                int nr = (cur.rs + 1) % rows[cur.o];
                if (dist[cur.o][nr][cur.cs] == -1) {
                    dist[cur.o][nr][cur.cs] = d + 1;
                    q.push({cur.o, nr, cur.cs});
                }
            }
            // down
            {
                int nr = (cur.rs - 1 + rows[cur.o]) % rows[cur.o];
                if (dist[cur.o][nr][cur.cs] == -1) {
                    dist[cur.o][nr][cur.cs] = d + 1;
                    q.push({cur.o, nr, cur.cs});
                }
            }
            // left
            {
                int nc = (cur.cs + 1) % cols[cur.o];
                if (dist[cur.o][cur.rs][nc] == -1) {
                    dist[cur.o][cur.rs][nc] = d + 1;
                    q.push({cur.o, cur.rs, nc});
                }
            }
            // right
            {
                int nc = (cur.cs - 1 + cols[cur.o]) % cols[cur.o];
                if (dist[cur.o][cur.rs][nc] == -1) {
                    dist[cur.o][cur.rs][nc] = d + 1;
                    q.push({cur.o, cur.rs, nc});
                }
            }
            // rotate left
            {
                int no = (cur.o + 1) % 4;
                int nrs = cur.cs;                                   // column shift becomes row shift
                int ncs = (rows[cur.o] - cur.rs) % rows[cur.o];      // old row shift becomes column shift
                if (dist[no][nrs][ncs] == -1) {
                    dist[no][nrs][ncs] = d + 1;
                    q.push({no, nrs, ncs});
                }
            }
            // rotate right
            {
                int no = (cur.o + 3) % 4;
                int nrs = (cols[cur.o] - cur.cs) % cols[cur.o];
                int ncs = cur.rs;
                if (dist[no][nrs][ncs] == -1) {
                    dist[no][nrs][ncs] = d + 1;
                    q.push({no, nrs, ncs});
                }
            }
        }

        const int INF = 1e9;
        int best = INF;
        bool bestSwap = false;

        // helper lambda: value at (r,c) for a given state
        auto getVal = [&](int o, int rs, int cs, int r, int c) -> int {
            int colp = c - cs;
            colp %= cols[o];
            if (colp < 0) colp += cols[o];
            int rowp = r - rs;
            rowp %= rows[o];
            if (rowp < 0) rowp += rows[o];
            int i, j;
            if (o == 0) {
                i = rowp; j = colp;
            } else if (o == 1) {
                i = M1 - 1 - colp;
                j = rowp;
            } else if (o == 2) {
                i = M1 - 1 - rowp;
                j = N1 - 1 - colp;
            } else { // o == 3
                i = colp;
                j = N1 - 1 - rowp;
            }
            return A[i][j];
        };

        for (int o = 0; o < 4; ++o) {
            if (rows[o] != M2 || cols[o] != N2) continue;
            for (int rs = 0; rs < rows[o]; ++rs) {
                for (int cs = 0; cs < cols[o]; ++cs) {
                    int d = dist[o][rs][cs];
                    if (d == -1) continue;
                    int mism = 0;
                    int r1=-1,c1=-1,r2=-1,c2=-1;
                    int a1=0,b1=0,a2=0,b2=0;
                    for (int r = 0; r < M2 && mism <= 2; ++r) {
                        for (int c = 0; c < N2 && mism <= 2; ++c) {
                            int a = getVal(o, rs, cs, r, c);
                            int b = B[r][c];
                            if (a != b) {
                                if (mism == 0) {
                                    r1=r; c1=c; a1=a; b1=b;
                                } else if (mism == 1) {
                                    r2=r; c2=c; a2=a; b2=b;
                                }
                                ++mism;
                            }
                        }
                    }
                    if (mism == 0) {
                        if (d < best) { best = d; bestSwap = false; }
                    } else if (mism == 2) {
                        if (a1 == b2 && a2 == b1) {
                            if (d + 1 < best) { best = d + 1; bestSwap = true; }
                        }
                    }
                }
            }
        }

        if (best == INF) {
            cout << msgFail << "\n";
        } else {
            cout << best;
            if (bestSwap) cout << ' ' << msgSwap;
            cout << "\n";
        }
    }
    return 0;
}
