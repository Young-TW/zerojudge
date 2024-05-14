#include <iostream>

int main() {
    int n;
    while (std::cin >> n) {
        std::cout << "'C' can use printf(\"%d\",n); to show integer like " << n
                  << std::endl;
    }
    return 0;
}