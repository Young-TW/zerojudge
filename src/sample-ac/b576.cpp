#include <iostream>

using namespace std;

int solve(int n, long long k) {
    if (n == 1) {
        if (k == 1) return 1;
        if (k == 2) return 2;
        return 3;
    }
    long long L = 3LL << (n - 2);
    if (k <= L) {
        return solve(n - 1, k);
    } else {
        return 4 - solve(n - 1, k - L);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    while (cin >> T) {
        while (T--) {
            long long K;
            cin >> K;
            cout << solve(32, K) << "\n";
        }
    }
    return 0;
}
