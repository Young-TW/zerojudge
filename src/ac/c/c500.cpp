#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int k, n, m, f;
    while (std::cin >> k >> n >> m >> f) {
        std::vector<int> damages(k);
        for (int i = 0; i < k; ++i) {
            std::cin >> damages[i];
        }
        std::sort(damages.begin(), damages.end(), std::greater<int>());
        
        int64_t total_damage = 0;
        for (int i = 0; i < k; ++i) {
            int64_t seat = 1LL + 1LL * i * f;
            if (seat > m) {
                total_damage += (seat - m) * damages[i];
            }
        }
        std::cout << total_damage << '\n';
    }
    return 0;
}
