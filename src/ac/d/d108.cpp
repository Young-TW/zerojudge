#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int digit_cost[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int max_val = 1000;
    vector<int> cost(max_val, 0);
    
    for (int i = 0; i < max_val; ++i) {
        int temp = i;
        if (temp == 0) {
            cost[i] = digit_cost[0];
        } else {
            int c = 0;
            while (temp > 0) {
                c += digit_cost[temp % 10];
                temp /= 10;
            }
            cost[i] = c;
        }
    }

    int n;
    while (cin >> n) {
        int ans = 0;
        for (int a = 0; a < max_val; ++a) {
            for (int b = 0; b < max_val; ++b) {
                int c = a + b;
                if (c >= max_val) continue;
                if (cost[a] + cost[b] + cost[c] + 4 == n) {
                    ++ans;
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
