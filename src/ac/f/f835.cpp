#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, G;
    if (!(cin >> T >> G)) return 0;

    const int dr[8] = {-1,-1,-1,0,0,1,1,1};
    const int dc[8] = {-1,0,1,-1,1,-1,0,1};

    while (T--) {
        long long totalComp = 0;          // C
        int bestSave = 0;                 // maximal (k-1)

        for (int gg = 0; gg < G; ++gg) {
            int M, N;
            cin >> M >> N;
            vector<string> grid(M);
            for (int i = 0; i < M; ++i) cin >> grid[i];

            int cells = M * N;
            vector<int> comp(cells, 0);   // 0 = not a giant, otherwise component id
            int curId = 0;

            // ----- 8‑connected components of 'D' -----
            vector<int> stack;
            stack.reserve(1024);
            for (int r = 0; r < M; ++r) {
                for (int c = 0; c < N; ++c) {
                    if (grid[r][c] != 'D') continue;
                    int idx = r * N + c;
                    if (comp[idx]) continue;
                    ++curId;
                    stack.clear();
                    stack.push_back(idx);
                    comp[idx] = curId;
                    while (!stack.empty()) {
                        int v = stack.back(); stack.pop_back();
                        int vr = v / N, vc = v % N;
                        for (int d = 0; d < 8; ++d) {
                            int nr = vr + dr[d];
                            int nc = vc + dc[d];
                            if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
                            if (grid[nr][nc] != 'D') continue;
                            int nid = nr * N + nc;
                            if (!comp[nid]) {
                                comp[nid] = curId;
                                stack.push_back(nid);
                            }
                        }
                    }
                }
            }
            totalComp += curId;   // add components of this map

            // ----- evaluate every empty cell -----
            for (int r = 0; r < M; ++r) {
                for (int c = 0; c < N; ++c) {
                    if (grid[r][c] != 'd') continue;
                    int ids[8];
                    int cnt = 0;
                    for (int d = 0; d < 8; ++d) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];
                        if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
                        int id = comp[nr * N + nc];
                        if (id == 0) continue;
                        bool seen = false;
                        for (int k = 0; k < cnt; ++k)
                            if (ids[k] == id) { seen = true; break; }
                        if (!seen) ids[cnt++] = id;
                    }
                    if (cnt >= 2) {
                        bestSave = max(bestSave, cnt - 1);
                    }
                }
            }
        } // end of G maps

        long long answer = totalComp - bestSave;
        if (bestSave > 0) {
            cout << answer << " DD好醜\n";
        } else {
            cout << answer << "\n";
        }
    }
    return 0;
}
