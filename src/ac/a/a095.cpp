#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long long N, M;
    while (std::cin >> N >> M) {
        long long ans = (N == M) ? M : (M + 1);
        std::cout << ans << '\n';
    }
    return 0;
}
