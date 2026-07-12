#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long C[55][55] = {0};
    for (int i = 0; i <= 50; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    int N;
    while (cin >> N) {
        while (N--) {
            int D, c;
            cin >> D >> c;
            unsigned long long ans = 0;
            int limit = min(D, c);
            for (int i = 0; i <= limit; ++i) {
                ans += C[c][i];
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
