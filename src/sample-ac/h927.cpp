#include <iostream>
#include <string>

const int MOD = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    while (std::cin >> n >> m) {
        std::string a, b;
        std::cin >> a >> b;
        long long value = 0;
        // Add reversed 1's from b (prepend all 1's)
        for (int i = m - 1; i >= 0; --i) {
            if (b[i] == '1') {
                value = (value * 2 + 1) % MOD;
            }
        }
        // Add original a
        for (char c : a) {
            value = (value * 2 + (c - '0')) % MOD;
        }
        // Add 0's from b in original order (append all 0's)
        for (int i = 0; i < m; ++i) {
            if (b[i] == '0') {
                value = (value * 2) % MOD;
            }
        }
        std::cout << value << "\n";
    }
    return 0;
}
