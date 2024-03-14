#include <iostream>

int main() {
    int num;
    while (std::cin >> num) {
        for (int i=1; i<num; i++) {
            if (i%7 == 0)
                continue;
            std::cout << i << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}