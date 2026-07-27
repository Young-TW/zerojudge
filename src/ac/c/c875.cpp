#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long A, B, C;
    while (cin >> A >> B >> C) {
        long long K = C / B;                 // maximal difference in cans
        vector<long long> h(A);
        long long sumOrig = 0;
        for (long long i = 0; i < A; ++i) {
            long long D;
            cin >> D;
            h[i] = D / B;                     // height in cans
            sumOrig += h[i];
        }

        // forward sweep
        for (long long i = 1; i < A; ++i) {
            long long limit = h[i - 1] + K;
            if (h[i] > limit) h[i] = limit;
        }
        // backward sweep
        for (long long i = A - 2; i >= 0; --i) {
            long long limit = h[i + 1] + K;
            if (h[i] > limit) h[i] = limit;
        }

        long long sumFinal = 0;
        for (long long v : h) sumFinal += v;

        cout << (sumOrig - sumFinal) << '\n';
    }
    return 0;
}
