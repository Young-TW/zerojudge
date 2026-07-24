#include <bits/stdc++.h>
using namespace std;

/* ---------- DLX structures ---------- */
struct DLX {
    // maximum possible nodes: header + columns + all 1's
    vector<int> L, R, U, D, C, rowSize;
    vector<int> colSize;          // number of nodes in each column
    int header;                   // node 0
    int nCol;                     // number of columns (m)
    int nodeCnt;                  // next free node index
    int maxRowSize;               // largest C_i in the current test case

    DLX(int nRows, int nColumns, int maxOnes) {
        nCol = nColumns;
        header = 0;
        int maxNodes = 1 + nColumns + maxOnes + 5;
        L.assign(maxNodes, 0);
        R.assign(maxNodes, 0);
        U.assign(maxNodes, 0);
        D.assign(maxNodes, 0);
        C.assign(maxNodes, 0);
        rowSize.assign(maxNodes, 0);
        colSize.assign(nColumns + 1, 0);
        initHeaders();
        nodeCnt = nColumns + 1;   // first free index after column headers
        maxRowSize = 0;
    }

    void initHeaders() {
        // header links all column headers (1..nCol) in a circular list
        L[header] = nCol;
        R[header] = 1;
        for (int i = 1; i <= nCol; ++i) {
            L[i] = i - 1;
            R[i] = i + 1;
            U[i] = D[i] = i;      // empty column
            C[i] = i;             // column number
        }
        R[nCol] = header;
        L[1] = header;
    }

    // add a row (rowId is only for possible debugging)
    void addRow(int rowId, const vector<int>& cols) {
        int first = -1;
        int prev = -1;
        int sz = cols.size();
        maxRowSize = max(maxRowSize, sz);
        for (int col : cols) {
            int nd = nodeCnt++;
            C[nd] = col;
            rowSize[nd] = rowId;

            // vertical link (insert just above the column header)
            U[nd] = U[col];
            D[nd] = col;
            D[U[col]] = nd;
            U[col] = nd;
            ++colSize[col];

            // horizontal link inside the row
            if (first == -1) {
                first = nd;
                L[nd] = R[nd] = nd;
            } else {
                L[nd] = prev;
                R[nd] = first;
                R[prev] = nd;
                L[first] = nd;
            }
            prev = nd;
        }
    }

    // ----- cover / uncover -----
    void cover(int c) {
        // remove column header
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        // remove rows
        for (int i = D[c]; i != c; i = D[i]) {
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --colSize[C[j]];
            }
        }
    }

    void uncover(int c) {
        for (int i = U[c]; i != c; i = U[i]) {
            for (int j = L[i]; j != i; j = L[j]) {
                ++colSize[C[j]];
                U[D[j]] = j;
                D[U[j]] = j;
            }
        }
        L[R[c]] = c;
        R[L[c]] = c;
    }

    // ----- heuristic lower bound -----
    int lowerBound() const {
        int remaining = 0;
        for (int c = R[header]; c != header; c = R[c])
            ++remaining;
        if (maxRowSize == 0) return INT_MAX;
        return (remaining + maxRowSize - 1) / maxRowSize;
    }

    // ----- recursive search with depth limit -----
    bool dfs(int depth, int limit) {
        if (R[header] == header) return true;          // all columns covered
        if (depth == limit) return false;
        if (depth + lowerBound() > limit) return false;

        // choose column with smallest size
        int c = R[header];
        int minSize = colSize[c];
        for (int j = R[c]; j != header; j = R[j]) {
            if (colSize[j] < minSize) {
                minSize = colSize[j];
                c = j;
            }
        }
        if (minSize == 0) return false;                // dead end

        cover(c);
        for (int r = D[c]; r != c; r = D[r]) {
            // cover other columns of this row
            for (int j = R[r]; j != r; j = R[j]) cover(C[j]);
            if (dfs(depth + 1, limit)) {
                // solution found, unwind without undoing (not needed)
                for (int j = L[r]; j != r; j = L[j]) uncover(C[j]);
                uncover(c);
                return true;
            }
            // backtrack
            for (int j = L[r]; j != r; j = L[j]) uncover(C[j]);
        }
        uncover(c);
        return false;
    }
};

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> rows(n);
        int totalOnes = 0;
        for (int i = 0; i < n; ++i) {
            int C; cin >> C;
            rows[i].resize(C);
            for (int j = 0; j < C; ++j) {
                cin >> rows[i][j];
            }
            totalOnes += C;
        }

        DLX dlx(n, m, totalOnes);
        for (int i = 0; i < n; ++i) {
            if (!rows[i].empty())
                dlx.addRow(i + 1, rows[i]);
        }

        bool impossible = false;
        for (int c = 1; c <= m; ++c) {
            if (dlx.colSize[c] == 0) {
                impossible = true;
                break;
            }
        }

        if (impossible) {
            cout << "No\n";
            continue;
        }

        int answer = -1;
        for (int limit = 1; limit <= m; ++limit) {
            if (dlx.dfs(0, limit)) {
                answer = limit;
                break;
            }
        }
        if (answer == -1) cout << "No\n";
        else               cout << answer << "\n";
    }
    return 0;
}
