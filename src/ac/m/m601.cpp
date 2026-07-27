#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while ( (cin >> N) ) {
        vector<long long> X(N), H(N);
        for (long long i = 0; i < N; ++i) {
            cin >> X[i] >> H[i];
        }
        long long answer = -1;
        for (long long i = 1; i < N; ++i) {
            long long d = X[i] - X[i-1];
            long long left  = 4LL * H[i-1] * H[i-1] - 4LL * d * d;
            long long right = H[i] * H[i];
            if (left < right) {
                answer = X[i];
                break;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
