#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, D;
    while (cin >> n >> D) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        long long total_profit = 0;
        bool holding = true;
        int last_price = a[0];

        for (int i = 1; i < n; ++i) {
            int y = a[i];
            if (holding) {
                if (y >= last_price + D) {
                    total_profit += y - last_price;
                    last_price = y;
                    holding = false;
                }
            } else {
                if (y <= last_price - D) {
                    last_price = y;
                    holding = true;
                }
            }
        }

        cout << total_profit << "\n";
    }

    return 0;
}
