#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int memo[501][501] = {};
    int N, X;

    while (cin >> N >> X) {
        if (N == 0 && X == 0) break;

        if (memo[N][X] != 0) {
            cout << memo[N][X] << '\n';
            continue;
        }

        int n = N - 1;          // remaining people after eliminating person 1
        int target = X - 2;     // 0-based index of the mayor in the remaining circle

        for (int M = 2; ; ++M) {
            int pos = 0;        // J(1) = 0
            for (int i = 2; i <= n; ++i) {
                pos = (pos + M) % i;
            }
            if (pos == target) {
                memo[N][X] = M;
                cout << M << '\n';
                break;
            }
        }
    }

    return 0;
}
