#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, M;
    while (cin >> N >> M) {
        // difference array, indices 0 .. M+1
        vector<long long> diff(static_cast<size_t>(M) + 2, 0);
        for (long long i = 0; i < N; ++i) {
            long long A, L, R;
            cin >> A >> L >> R;
            diff[static_cast<size_t>(L)] += A;
            if (R + 1 <= M) {
                diff[static_cast<size_t>(R + 1)] -= A;
            }
            // if R == M, R+1 is out of the considered range, nothing to do
        }

        long long cur = 0;
        long long bestSum = -1;
        long long bestPos = -1;
        for (long long x = 0; x <= M; ++x) {
            cur += diff[static_cast<size_t>(x)];
            if (cur > bestSum || (cur == bestSum && x < bestPos)) {
                bestSum = cur;
                bestPos = x;
            }
        }
        cout << bestPos << ' ' << bestSum << '\n';
    }
    return 0;
}
