#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<int> coins(n);
            for (int i = 0; i < n; ++i) {
                cin >> coins[i];
            }

            int count = 1;
            int sum = coins[0];
            for (int i = 1; i < n - 1; ++i) {
                if (sum < coins[i]) {
                    sum += coins[i];
                    ++count;
                }
            }
            if (sum < coins.back()) {
                ++count;
            }

            cout << count << '\n';
        }
    }

    return 0;
}
