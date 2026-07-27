#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        if (N == 0) break;
        vector<vector<int>> A(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cin >> A[i][j];

        int Q;
        cin >> Q;
        while (Q--) {
            int r1, r2, c1, c2;
            cin >> r1 >> r2 >> c1 >> c2;

            // 1st pass : Boyer–Moore
            int cand = 0;
            int cnt = 0;
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    int x = A[i][j];
                    if (cnt == 0) {
                        cand = x;
                        cnt = 1;
                    } else if (cand == x) {
                        ++cnt;
                    } else {
                        --cnt;
                    }
                }
            }

            // 2nd pass : count occurrences of cand
            int occ = 0;
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    if (A[i][j] == cand) ++occ;
                }
            }

            int total = (r2 - r1 + 1) * (c2 - c1 + 1);
            if (occ * 2 > total)
                cout << cand << '\n';
            else
                cout << -1 << '\n';
        }
    }
    return 0;
}
