#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a > b) std::swap(a,b);
    if (b > c) std::swap(b,c);
    if (a > b) std::swap(a,b);

    std::cout << a << " " << b << " " << c << std::endl;

    if (a + b <= c) {
        std::cout << "No";
    } else if ((a*a) + (b*b) < c*c) {
        std::cout << "Obtuse";
    } else if ((a*a) + (b*b) == c*c) {
        std::cout << "Right";
    } else if ((a*a) + (b*b) > c*c) {
        std::cout << "Acute";
    }

    return 0;
}