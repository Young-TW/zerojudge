#include <iostream>

void printNum(int num) {
    for (int i = 0; i < num; i++) std::cout << num;
    std::cout << std::endl;
}

int main() {
    int n, a, f;
    std::cin >> n;
    while (n > 0) {
        std::cin >> f >> a;
        for (int k = 0; k <= a; k++) {
            for (int j = 0; j < f; j++) printNum(j);
            for (int j = f; j > 0; j--) printNum(j);
            std::cout << std::endl;
        }

        n--;
    }

    return 0;
}

// 00488 - Triangle Wave