#include <iostream>

int main() {
    int day;
    int manto;
    long long int tt = 0;
    std::cin >> day;
    for (int i = 1; i <= day; i++) {
        std::cin >> manto;
        tt += (i * manto);
    }
    std::cout << tt << std::endl;
    return 0;
}