#include <iostream>
#include <string>

int main() {
    std::string num, temp;
    int n, a, b;
    std::cin >> num >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        a = 0;
        b = 0;
        for (int j = 0; j < 4; j++) {
            if (num.at(j) == temp.at(j)) {
                a++;
            } else {
                for (int k = 0; k < 4; k++) {
                    if (num.at(j) == temp.at(k) && j != k) {
                        b++;
                    }
                }
            }
        }
        std::cout << a << "A" << b << "B" << std::endl;
    }
    return 0;
}