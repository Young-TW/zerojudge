#include <iostream>
#include <string>

int main() {
    std::string n, m;
    int i = 0;
    std::cin >> n;
    while (std::cin >> m) {
        if (i) {
            std::cout << " " << n << " ";
        }
        std::cout << m;
        i++;
    }
    return 0;
}