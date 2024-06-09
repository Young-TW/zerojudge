#include <iostream>

int main() {
    double n, tt, reg;
    while (std::cin >> n) {
        tt = 0;
        for (int i = 0; i < n; i++) {
            std::cin >> reg;
            tt += reg;
        }

        if ((tt / n) > 59)
            std::cout << "no" << std::endl;
        else
            std::cout << "yes" << std::endl;
    }

    return 0;
}