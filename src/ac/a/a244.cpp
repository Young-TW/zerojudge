#include <iostream>

int main() {
    int n, a;
    long long int b, c;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b >> c;
        switch (a) {
            case 1:
                std::cout << b + c << std::endl;
                break;
            case 2:
                std::cout << b - c << std::endl;
                break;
            case 3:
                std::cout << b * c << std::endl;
                break;
            case 4:
                std::cout << b / c << std::endl;
                break;
        }
    }

    return 0;
}