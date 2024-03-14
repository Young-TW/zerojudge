#include <iostream>

int main() {
    long long int n, m, sum, count;
    while (std::cin >> n >> m) {
        sum = 0;
        count = 0;
        do {
            sum += n + count++;
        } while (sum <= m);
        std::cout << count << std::endl;
    }

    return 0;
}