#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, m;
    while (std::cin >> n >> m) {
        long long ans = 6 + 4 * (m - 1) + (n - 1) * (3 * m + 2);
        std::cout << ans << '\n';
    }
    return 0;
}
