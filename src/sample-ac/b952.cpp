#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long length;
    while (cin.peek() != EOF) {
        vector<long long> sticks;
        while (cin >> length) {
            sticks.push_back(length);
            if (cin.get() == '\n') break;
        }

        if (sticks.empty()) continue;

        long long total_sum = 0;
        for (long long s : sticks) {
            total_sum += s;
        }

        long long max_a = 0;
        long long half_sum = total_sum / 2;

        // DP for subset sum
        // dp[i] = true if sum i is achievable
        // We only need up to half_sum
        vector<bool> dp(half_sum + 1, false);
        dp[0] = true;

        for (long long s : sticks) {
            for (long long j = half_sum; j >= s; --j) {
                if (dp[j - s]) {
                    dp[j] = true;
                }
            }
        }

        // Find the largest achievable sum <= half_sum
        for (long long i = half_sum; i >= 0; --i) {
            if (dp[i]) {
                max_a = i;
                break;
            }
        }

        long long max_b = total_sum - max_a;
        cout << max_a * max_b << "\n";
    }

    return 0;
}
