#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000007;

void solve() {
    long long N, M, K;
    cin >> N >> M >> K;

    for (int day = 0; day < K; ++day) {
        long long new_ants = 0;
        if (N > M) {
            new_ants = (N * 2) % MOD;
        } else if (M > N) {
            new_ants = (M * 2) % MOD;
        } else {
            new_ants = (N * 2) % MOD;
        }

        long long new_N = (M + new_ants) % MOD;
        long long new_M = (N) % MOD;

        N = new_N;
        M = new_M;
    }

    cout << N << " " << M << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
