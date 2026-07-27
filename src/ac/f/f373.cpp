#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long N;
    while (std::cin >> N) {
        long long price0 = N - (N / 2000) * 200;
        long long price1 = N - (N / 1000) * 100;

        if (price0 <= price1) {
            std::cout << price0 << " 0\n";
        } else {
            std::cout << price1 << " 1\n";
        }
    }
    return 0;
}
