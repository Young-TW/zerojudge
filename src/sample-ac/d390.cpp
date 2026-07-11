#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        while (N--) {
            int m;
            cin >> m;
            vector<int> coins(m);
            int sum = 0;
            for (int i = 0; i < m; ++i) {
                cin >> coins[i];
                sum += coins[i];
            }

            int capacity = sum / 2;
            bitset<25005> dp;
            dp[0] = 1;

            for (int i = 0; i < m; ++i) {
                dp |= (dp << coins[i]);
            }

            int s1 = 0;
            for (int j = capacity; j >= 0; --j) {
                if (dp[j]) {
                    s1 = j;
                    break;
                }
            }

            cout << sum - 2 * s1 << "\n";
        }
    }

    return 0;
}
