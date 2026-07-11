#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

int main() {
    long long n, m;
    while (cin >> n >> m) {
        int deno[6] = {500, 100, 50, 10, 5, 1};
        int orig[6] = {0};
        long long temp = n;
        if (temp >= 500) {
            orig[0] = 1;
            temp -= 500;
        }
        orig[1] = min(4, (int)(temp / 100));
        temp -= orig[1] * 100;
        if (temp >= 50) {
            orig[2] = 1;
            temp -= 50;
        }
        orig[3] = min(4, (int)(temp / 10));
        temp -= orig[3] * 10;
        if (temp >= 5) {
            orig[4] = 1;
            temp -= 5;
        }
        orig[5] = (int)temp;
        vector<int> coins;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < orig[i]; j++) {
                coins.push_back(i);
            }
        }
        int total_coins = coins.size();
        int best_coins = INT_MAX;
        long long best_p = -1;
        int total_subsets = 1 << total_coins;
        for (int mask = 0; mask < total_subsets; mask++) {
            long long p = 0;
            int sub[6] = {0};
            for (int j = 0; j < total_coins; j++) {
                if (mask & (1 << j)) {
                    int idx = coins[j];
                    p += deno[idx];
                    sub[idx]++;
                }
            }
            if (p < m) continue;
            long long change = p - m;
            int change_cnt[6] = {0};
            for (int i = 0; i < 6; i++) {
                change_cnt[i] = change / deno[i];
                change %= deno[i];
            }
            int total = 0;
            for (int i = 0; i < 6; i++) {
                total += orig[i] - sub[i] + change_cnt[i];
            }
            if (total < best_coins || (total == best_coins && p < best_p)) {
                best_coins = total;
                best_p = p;
            }
        }
        cout << best_p << endl;
    }
    return 0;
}
