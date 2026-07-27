#include <bits/stdc++.h>
using namespace std;

struct State {
    int mn, mx, cur;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while (cin >> N) {
        int M;
        string S;
        cin >> M >> S;
        // ---------- enumerate states ----------
        const int SHIFT = 2;                 // to make indices non‑negative
        int idMap[5][5][5];
        memset(idMap, -1, sizeof(idMap));
        vector<State> states;
        for (int mn = -2; mn <= 2; ++mn) {
            for (int mx = mn; mx <= mn + 2 && mx <= 2; ++mx) {
                for (int cur = mn; cur <= mx; ++cur) {
                    State st{mn, mx, cur};
                    int id = (int)states.size();
                    states.push_back(st);
                    idMap[mn + SHIFT][mx + SHIFT][cur + SHIFT] = id;
                }
            }
        }
        const int SNUM = (int)states.size(); // should be 22

        // ---------- transitions ----------
        vector<int> transL(SNUM, -1), transP(SNUM, -1);
        for (int id = 0; id < SNUM; ++id) {
            const State &st = states[id];
            // L : +1
            int ncur = st.cur + 1;
            int nmn = min(st.mn, ncur);
            int nmx = max(st.mx, ncur);
            if (nmx - nmn <= 2 && ncur >= -2 && ncur <= 2) {
                transL[id] = idMap[nmn + SHIFT][nmx + SHIFT][ncur + SHIFT];
            }
            // P : -1
            ncur = st.cur - 1;
            nmn = min(st.mn, ncur);
            nmx = max(st.mx, ncur);
            if (nmx - nmn <= 2 && ncur >= -2 && ncur <= 2) {
                transP[id] = idMap[nmn + SHIFT][nmx + SHIFT][ncur + SHIFT];
            }
        }

        // ---------- DP table ----------
        // dp[len * SNUM + id]  (len = 0 … N)
        vector<uint32_t> dp((N + 1) * SNUM);
        for (int id = 0; id < SNUM; ++id) dp[id] = 1 % M; // len = 0

        for (long long len = 1; len <= N; ++len) {
            uint32_t *curRow = &dp[len * SNUM];
            uint32_t *prevRow = &dp[(len - 1) * SNUM];
            for (int id = 0; id < SNUM; ++id) {
                uint32_t sum = 0;
                int t = transL[id];
                if (t != -1) sum += prevRow[t];
                t = transP[id];
                if (t != -1) {
                    sum += prevRow[t];
                    if (sum >= (uint32_t)M) sum -= M; // at most 2M-2
                }
                if (sum >= (uint32_t)M) sum -= M;
                curRow[id] = sum;
            }
        }

        // ---------- rank ----------
        int startId = idMap[0 + SHIFT][0 + SHIFT][0 + SHIFT]; // mn=mx=cur=0
        int curId = startId;
        uint32_t rank = 1 % M; // numbering starts from 1
        for (long long i = 0; i < N; ++i) {
            char ch = S[i];
            long long rem = N - i - 1;
            if (ch == 'P') { // smaller character is 'L'
                int alt = transL[curId];
                if (alt != -1) {
                    rank += dp[rem * SNUM + alt];
                    if (rank >= (uint32_t)M) rank -= M;
                }
            }
            // move according to the real character
            curId = (ch == 'L') ? transL[curId] : transP[curId];
        }
        cout << rank % M << '\n';
    }
    return 0;
}
