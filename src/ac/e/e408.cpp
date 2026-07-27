#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, l;
    while (cin >> n >> p >> l) {
        /* position tables, -1 means the number is not on the board */
        vector<int> rowB(l + 1, -1), colB(l + 1, -1);
        vector<int> rowA(l + 1, -1), colA(l + 1, -1);

        /* Baluteshih board */
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x; cin >> x;
                rowB[x] = i;
                colB[x] = j;
            }
        }
        /* Alan board */
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x; cin >> x;
                rowA[x] = i;
                colA[x] = j;
            }
        }

        vector<int> rCntB(n, 0), cCntB(n, 0);
        vector<int> rCntA(n, 0), cCntA(n, 0);
        int d1B = 0, d2B = 0, d1A = 0, d2A = 0;
        int linesB = 0, linesA = 0;
        int lastNum = 0;
        bool finished = false;

        for (int i = 0; i < l; ++i) {
            int num; cin >> num;
            if (!finished) {
                lastNum = num;

                /* Baluteshih marks */
                int r = rowB[num];
                if (r != -1) {
                    int c = colB[num];
                    if (++rCntB[r] == n) ++linesB;
                    if (++cCntB[c] == n) ++linesB;
                    if (r == c) {
                        if (++d1B == n) ++linesB;
                    }
                    if (r + c == n - 1) {
                        if (++d2B == n) ++linesB;
                    }
                }

                /* Alan marks */
                r = rowA[num];
                if (r != -1) {
                    int c = colA[num];
                    if (++rCntA[r] == n) ++linesA;
                    if (++cCntA[c] == n) ++linesA;
                    if (r == c) {
                        if (++d1A == n) ++linesA;
                    }
                    if (r + c == n - 1) {
                        if (++d2A == n) ++linesA;
                    }
                }

                if (linesB >= p || linesA >= p) {
                    finished = true;          // still read remaining numbers
                }
            }
            /* else: already finished, just discard the number */
        }

        string result;
        if (linesB >= p && linesA >= p) {
            result = "Draw";
        } else if (linesB >= p) {
            result = "The winner is Baluteshih";
        } else if (linesA >= p) {
            result = "The winner is Alan";
        } else {
            if (linesB > linesA) result = "The winner is Baluteshih";
            else if (linesA > linesB) result = "The winner is Alan";
            else result = "Draw";
        }

        cout << lastNum << ' ' << linesB << ' ' << linesA << '\n';
        cout << result << '\n';
    }
    return 0;
}
