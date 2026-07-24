#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, M;
    while (cin >> N >> M) {
        // read matrix in column‑major order
        vector<vector<long long>> a(N, vector<long long>(M));
        for (long long col = 0; col < M; ++col) {
            for (long long row = 0; row < N; ++row) {
                long long v;
                cin >> v;
                a[row][col] = v;
            }
        }

        // build 2D prefix sum (size (N+1) x (M+1))
        vector<vector<long long>> pref(N + 1, vector<long long>(M + 1, 0));
        for (long long i = 0; i < N; ++i) {
            long long rowSum = 0;
            for (long long j = 0; j < M; ++j) {
                rowSum += a[i][j];
                pref[i + 1][j + 1] = pref[i][j + 1] + rowSum;
            }
        }

        int Q;
        cin >> Q;
        vector<long long> answers;
        answers.reserve(Q);
        for (int q = 0; q < Q; ++q) {
            long long r1, r2, c1, c2;
            cin >> r1 >> r2 >> c1 >> c2;
            // ensure order (though problem guarantees r1<=r2, c1<=c2)
            if (r1 > r2) swap(r1, r2);
            if (c1 > c2) swap(c1, c2);
            long long sum = pref[r2 + 1][c2 + 1] - pref[r1][c2 + 1]
                          - pref[r2 + 1][c1] + pref[r1][c1];
            answers.push_back(sum);
        }

        // output answers on one line separated by space
        for (size_t i = 0; i < answers.size(); ++i) {
            if (i) cout << ' ';
            cout << answers[i];
        }
        cout << '\n';
    }
    return 0;
}
