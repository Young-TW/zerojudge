#include <iostream>
#include <cstring>
using namespace std;

int n, sz;
int grid[9][9];
int rowMask[9], colMask[9], boxMask[9];

int boxIdx(int r, int c) {
    return (r / n) * n + (c / n);
}

bool solve(int pos) {
    if (pos == sz * sz) return true;
    int r = pos / sz, c = pos % sz;
    if (grid[r][c] != 0) return solve(pos + 1);
    int b = boxIdx(r, c);
    for (int v = 1; v <= sz; v++) {
        int bit = 1 << v;
        if ((rowMask[r] & bit) || (colMask[c] & bit) || (boxMask[b] & bit)) continue;
        grid[r][c] = v;
        rowMask[r] |= bit;
        colMask[c] |= bit;
        boxMask[b] |= bit;
        if (solve(pos + 1)) return true;
        grid[r][c] = 0;
        rowMask[r] &= ~bit;
        colMask[c] &= ~bit;
        boxMask[b] &= ~bit;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool first = true;
    while (cin >> n) {
        if (!first) cout << "\n";
        first = false;
        sz = n * n;
        memset(rowMask, 0, sizeof(rowMask));
        memset(colMask, 0, sizeof(colMask));
        memset(boxMask, 0, sizeof(boxMask));
        bool valid = true;
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                cin >> grid[i][j];
                if (grid[i][j] != 0) {
                    int bit = 1 << grid[i][j];
                    int b = boxIdx(i, j);
                    if ((rowMask[i] & bit) || (colMask[j] & bit) || (boxMask[b] & bit)) {
                        valid = false;
                    }
                    rowMask[i] |= bit;
                    colMask[j] |= bit;
                    boxMask[b] |= bit;
                }
            }
        }
        if (!valid || !solve(0)) {
            cout << "NO SOLUTION\n";
        } else {
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    if (j) cout << " ";
                    cout << grid[i][j];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
