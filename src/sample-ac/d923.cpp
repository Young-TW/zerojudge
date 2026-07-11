#include <iostream>
#include <cstdint>
#include <cstring>

void print_uint128(unsigned __int128 x) {
    if (x == 0) {
        std::cout << '0';
        return;
    }
    char buf[40];
    int len = 0;
    while (x > 0) {
        buf[len++] = '0' + static_cast<char>(x % 10);
        x /= 10;
    }
    for (int i = len - 1; i >= 0; --i) {
        std::cout << buf[i];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    uint64_t I, J;
    while (std::cin >> I >> J) {
        unsigned __int128 i = I;
        unsigned __int128 j = J;
        unsigned __int128 ans = i * i * j;
        print_uint128(ans);
        std::cout << '\n';
    }
    return 0;
}
