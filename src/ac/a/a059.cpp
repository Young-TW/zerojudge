#include <cmath>
#include <iostream>

int main() {
    int a, n, m, tt = 0;
    std::cin >> a;
    for (int i = 0; i < a; i++) {
        std::cin >> n >> m;
        for (int j = n; j < m; j++) {
            if (sqrt(j) == int(sqrt(j))) {
                tt += j;
            }
        }

        std::cout << "Case " << i + 1 << ": " << tt << std::endl;
        tt = 0;
    }

    return 0;
}