#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    while (std::cin >> n && n != 0) {
        long long ans = static_cast<long long>(n) * (n + 1) * (2 * n + 1) / 6;
        std::cout << ans << "\n";
    }
    
    return 0;
}
