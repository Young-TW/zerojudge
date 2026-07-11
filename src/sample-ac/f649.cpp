#include <iostream>
#include <cmath>

int main() {
    long long N, M;
    while (std::cin >> N >> M) {
        if (N == 0) {
            std::cout << 1 << "\n";
            continue;
        }
        if (N == 1 || M == 0) {
            std::cout << 1 << "\n";
            continue;
        }
        
        double log_val = M * std::log10(static_cast<double>(N));
        long long digits_of_weight = static_cast<long long>(std::floor(log_val)) + 1;
        
        if (digits_of_weight == 0) {
            std::cout << 1 << "\n";
        } else {
            double log_digits = std::log10(static_cast<double>(digits_of_weight));
            long long result = static_cast<long long>(std::floor(log_digits)) + 1;
            std::cout << result << "\n";
        }
    }
    return 0;
}
