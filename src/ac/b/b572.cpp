#include <iostream>

int main() {
    int n;
    short m1, m2, h1, h2, t;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> h1 >> m1 >> h2 >> m2 >> t;
        m1 = 60 * h1 + m1;
        m2 = 60 * h2 + m2;
        if (t > m2 - m1) {
            std::cout << "No" << std::endl;
        } else {
            std::cout << "Yes" << std::endl;
        }
    }
    return 0;
}