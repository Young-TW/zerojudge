#include <iostream>

int main() {
    int t, n, m, tt;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cin >> n >> m;
        tt = 0;
        if (n % 2 == 0) n++;
        for (int j = n; j <= m; j += 2) {
            tt += j;
        }
        std::cout << "Case " << i + 1 << ": " << tt << std::endl;
    }
    return 0;
}