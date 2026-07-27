#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        int N;
        if (!(cin >> N)) break;
        vector<long long> da(N), db(N);
        for (int i = 0; i < N; ++i) {
            long long x, y;
            cin >> x >> y;
            long long dx = x - x1, dy = y - y1;
            da[i] = dx * dx + dy * dy;
            dx = x - x2; dy = y - y2;
            db[i] = dx * dx + dy * dy;
        }

        // sort by da, keep corresponding db
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return da[a] < da[b]; });

        vector<long long> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            A[i] = da[idx[i]];
            B[i] = db[idx[i]];
        }

        // suffix maximum of B
        vector<long long> suffix(N + 1, 0);
        for (int i = N - 1; i >= 0; --i) {
            suffix[i] = max(suffix[i + 1], B[i]);
        }

        long long best = LLONG_MAX;
        for (int k = 0; k <= N; ++k) {
            long long R1 = (k == 0) ? 0 : A[k - 1];
            long long R2 = suffix[k];
            best = min(best, R1 + R2);
        }
        cout << best << '\n';
    }
    return 0;
}
