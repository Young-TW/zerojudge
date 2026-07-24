#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            long long e;
            cin >> n >> e;
            vector<int> S(n);
            long long total_S = 0;
            for (int i = 0; i < n; ++i) {
                cin >> S[i];
                total_S += S[i];
            }

            long long target = (e + 1) / 2;

            if (total_S < target) {
                cout << "FULL\n";
            } else {
                bitset<200005> dp;
                dp[0] = 1;
                for (int i = 0; i < n; ++i) {
                    dp |= (dp << S[i]);
                }
                for (int i = target; i <= total_S; ++i) {
                    if (dp[i]) {
                        cout << i << "\n";
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
