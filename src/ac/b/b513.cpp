#include <iostream>
int main() {
    int n, m;
    std::cin >> n;
    bool prime = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> m;
        for (int j = 2; j < m / 2; j++) {
            if (m % j == 0) {
                prime = 1;
            }
        }

        if (!prime)
            std::cout << "Y" << std::endl;
        else
            std::cout << "N" << std::endl;
        prime = 0;
    }
    return 0;
}