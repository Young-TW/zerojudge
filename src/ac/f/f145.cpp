#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MAX_N = 10000;
    vector<long double> S(MAX_N + 1, 0.0L);
    vector<long double> U(MAX_N + 1, 0.0L);
    vector<long double> ans(MAX_N + 1, 0.0L);

    for (int i = 1; i <= MAX_N; ++i) {
        S[i] = S[i - 1] + log10l((long double)i);
    }
    for (int i = 1; i <= MAX_N; ++i) {
        U[i] = U[i - 1] + S[i];
    }
    for (int i = 1; i <= MAX_N; ++i) {
        ans[i] = ans[i - 1] + U[i];
    }

    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            if (cin >> n) {
                long double val = ans[n];
                long long digits = (long long)floorl(val);
                if (val - digits < 1e-5L) {
                    cout << digits + 1 << "\n";
                } else if (digits + 1 - val < 1e-5L) {
                    cout << digits + 2 << "\n";
                } else {
                    cout << digits + 1 << "\n";
                }
            }
        }
    }

    return 0;
}
