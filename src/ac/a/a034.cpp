#include <iostream>

void toBinary(int num) {
    int i;
    int ar[32];
    for (i = 0; num > 0; i++) {
        ar[i] = num % 2;
        num = num / 2;
    }

    for (int n = i - 1; n >= 0; n--) {
        std::cout << ar[n];
    }

    std::cout << std::endl;
    return;
}

int main() {
    int num;
    while (std::cin >> num) {
        toBinary(num);
    }

    return 0;
}