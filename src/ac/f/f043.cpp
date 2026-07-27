#include <iostream>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long long R, A;
    while (std::cin >> R >> A) {
        if (A == R) {
            A = R - 3;               // avoid a zero addend
        }
        long long x = std::min(A, R - A);
        long long y = std::max(A, R - A);
        std::cout << x << '+' << y << '=' << R << '\n';
    }
    return 0;
}
