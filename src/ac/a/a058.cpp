#include <iostream>

int main() {
    int n;
    int a = 0, b = 0, c = 0, inp;
    std::cin >> n;
    for (int d = 0; d < n; d++) {
        std::cin >> inp;
        if (inp % 3 == 0) {
            a++;
        } else if (inp % 3 == 1) {
            b++;
        } else {
            c++;
        }
    }

    std::cout << a << " " << b << " " << c;
    return 0;
}