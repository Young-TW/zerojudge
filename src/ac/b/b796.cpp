#include <bits/stdc++.h>
using namespace std;

int L;
vector<string> grid;

/* per cell data */
int powerCell[12][12];
long long costCell[12][12];

/* candidates per row */
vector<int> cand[12];
int rowBest[12];                 // maximal power in this row
int orderRows[12];               // rows processed in this order
int suffixBest[13];              // optimistic remaining power

bool placed[12][12];
bool bestPlaced[12][12];

int bestPower;
long long bestCost;
int bestCnt;

/* queen directions */
const int dr[8] = {-1,-1,-1,0,0,1,1,1};
const int dc[8] = {-1,0,1,-1,1,-1,0,1};

/* --------------------------------------------------------------- */
int calcPower(int r, int c) {
    int cnt = 0;
    for (int d = 0; d < 8; ++d) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        while (nr >= 0 && nr < L && nc >= 0 && nc < L) {
            if (grid[nr][nc] == 'x') ++cnt;
            nr += dr[d];
            nc += dc[d];
        }
    }
    return cnt;
}

/* --------------------------------------------------------------- */
void dfs(int pos, int colMask, int d1Mask, int d2Mask,
         int curPower, long long curCost, int curCnt) {
    if (pos == L) {
        if (curPower > bestPower ||
            (curPower == bestPower && curCost < bestCost)) {
            bestPower = curPower;
            bestCost  = curCost;
            bestCnt   = curCnt;
            for (int i = 0; i < L; ++i)
                for (int j = 0; j < L; ++j)
                    bestPlaced[i][j] = placed[i][j];
        }
        return;
    }

    if (curPower + suffixBest[pos] < bestPower) return;   // prune

    int r = orderRows[pos];

    /* option 1 : skip this row */
    dfs(pos + 1, colMask, d1Mask, d2Mask,
        curPower, curCost, curCnt);

    /* option 2 : place a cannon in this row */
    for (int c : cand[r]) {
        int colBit = 1 << c;
        int d1 = r - c + L - 1;          // 0 … 2L-2
        int d2 = r + c;                  // 0 … 2L-2
        int d1Bit = 1 << d1;
        int d2Bit = 1 << d2;
        if ( (colMask & colBit) || (d1Mask & d1Bit) || (d2Mask & d2Bit) )
            continue;                    // conflict

        placed[r][c] = true;
        dfs(pos + 1,
            colMask | colBit,
            d1Mask | d1Bit,
            d2Mask | d2Bit,
            curPower + powerCell[r][c],
            curCost  + costCell[r][c],
            curCnt + 1);
        placed[r][c] = false;
    }
}

/* --------------------------------------------------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        cin >> L;
        grid.assign(L, "");
        for (int i = 0; i < L; ++i) cin >> grid[i];

        /* clear per‑test data */
        for (int i = 0; i < L; ++i) {
            cand[i].clear();
            rowBest[i] = 0;
        }
        memset(placed, 0, sizeof(placed));
        memset(bestPlaced, 0, sizeof(bestPlaced));
        bestPower = 0;
        bestCost  = LLONG_MAX;
        bestCnt   = 0;

        /* pre‑compute power and cost */
        for (int r = 0; r < L; ++r) {
            for (int c = 0; c < L; ++c) {
                long long p = 1LL * (r + 1) * (r + 1) * (r + 1)
                              * (c + 1) * (c + 1);
                costCell[r][c] = p;
                if (grid[r][c] == '.') {
                    int pw = calcPower(r, c);
                    powerCell[r][c] = pw;
                    if (pw > 0) {               // zero‑power cells are useless
                        cand[r].push_back(c);
                        rowBest[r] = max(rowBest[r], pw);
                    }
                } else {
                    powerCell[r][c] = 0;
                }
            }
        }

        /* order rows by decreasing number of candidates (heuristic) */
        vector<int> rows(L);
        iota(rows.begin(), rows.end(), 0);
        sort(rows.begin(), rows.end(),
             [&](int a, int b){ return cand[a].size() > cand[b].size(); });
        for (int i = 0; i < L; ++i) orderRows[i] = rows[i];

        /* suffix of optimistic remaining power */
        suffixBest[L] = 0;
        for (int i = L - 1; i >= 0; --i) {
            suffixBest[i] = suffixBest[i + 1] + rowBest[ orderRows[i] ];
        }

        dfs(0, 0, 0, 0, 0, 0LL, 0);

        /* build answer map */
        vector<string> ansMap = grid;
        for (int r = 0; r < L; ++r)
            for (int c = 0; c < L; ++c)
                if (bestPlaced[r][c]) ansMap[r][c] = 'C';

        /* output */
        cout << "Quantity: " << bestCnt << "\n";
        cout << "Cost: " << bestCost << "\n";
        cout << "Power: " << bestPower << "\n";
        cout << "Strategy Map:\n";
        for (int r = 0; r < L; ++r) cout << ansMap[r] << "\n";
    }
    return 0;
}
