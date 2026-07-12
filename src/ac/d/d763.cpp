#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstdint>

// Print unsigned __int128
void print_uint128(unsigned __int128 x) {
    if (x == 0) {
        std::cout << 0;
        return;
    }
    std::string s;
    while (x > 0) {
        int digit = x % 10;
        s.push_back('0' + digit);
        x /= 10;
    }
    std::reverse(s.begin(), s.end());
    std::cout << s;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::vector<int> a;
        int x;
        while (ss >> x) {
            a.push_back(x);
        }

        // Termination condition: a single 0
        if (a.size() == 1 && a[0] == 0) {
            break;
        }

        std::sort(a.begin(), a.end());
        int n = a.size();

        if (n < 3) {
            std::cout << 0 << '\n';
            continue;
        }

        int max_val = a.back();
        std::vector<unsigned __int128> dp(max_val + 1);
        dp[0] = 1;

        unsigned __int128 total_subsets = 1; // 2^0
        unsigned __int128 answer = 0;
        int cur_max = 0;

        for (int val : a) {
            // Count subsets with sum <= val
            unsigned __int128 count_le = 0;
            int limit = std::min(val, cur_max);
            for (int s = 0; s <= limit; ++s) {
                count_le += dp[s];
            }
            answer += total_subsets - count_le;

            // Update DP with current val
            int new_max = std::min(max_val, cur_max + val);
            for (int s = cur_max; s >= 0; --s) {
                if (dp[s] != 0) {
                    int ns = s + val;
                    if (ns <= max_val) {
                        dp[ns] += dp[s];
                    }
                }
            }
            cur_max = new_max;
            total_subsets <<= 1; // multiply by 2
        }

        print_uint128(answer);
        std::cout << '\n';
    }
    return 0;
}
