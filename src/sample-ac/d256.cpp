#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;
    while (T--) {
        long long G, L;
        std::cin >> G >> L;
        if (L % G == 0) {
            std::cout << G << ' ' << L << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }
    return 0;
}
