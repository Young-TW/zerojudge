#include <iostream>

long long int f(int n) {
    if (n == 1) return 1;
    return (n + f(n - 1));
}

long long int g(int n) {
    if (n == 1) return 1;
    return (f(n) + g(n - 1));
}

int main() {
    int n;
    while (std::cin >> n) {
        std::cout << f(n) << " " << g(n) << std::endl;
    }

    return 0;
}