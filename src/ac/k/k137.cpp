#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long long a, b;
    while (std::cin >> a >> b) {
        long long res = 1;
        long long base = a;
        long long exp = b;
        
        while (exp > 0) {
            if (exp & 1) {
                res *= base;
            }
            base *= base;
            exp >>= 1;
        }
        
        std::cout << a << "^" << b << " = " << res << "\n";
    }
    
    return 0;
}
