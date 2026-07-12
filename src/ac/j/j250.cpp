#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned long long C[55][55] = {0};
    for (int i = 0; i <= 50; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    int N, K;
    unsigned long long M;
    while (cin >> N >> K >> M) {
        string ans = "";
        int rem_K = K;
        int rem_N = N;
        for (int i = 0; i < N; ++i) {
            if (rem_K == 0) {
                ans += '0';
                continue;
            }
            unsigned long long cnt = C[rem_N - 1][rem_K];
            if (M <= cnt) {
                ans += '0';
            } else {
                ans += '1';
                M -= cnt;
                rem_K--;
            }
            rem_N--;
        }
        cout << ans << "\n";
    }

    return 0;
}
