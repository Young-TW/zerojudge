#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;                     // budget in TWD
    while (std::cin >> n) {
        long long m;                 // spent amount
        char c;                      // currency letter
        if (!(std::cin >> m >> c)) break;

        long long p = 1, q = 1;      // rate = p / q (TWD per foreign unit)
        if (c == 'U') { p = 309; q = 10; }   // 30.9
        else if (c == 'J') { p = 7;   q = 25; }   // 0.28
        else if (c == 'E') { p = 69;  q = 2; }    // 34.5
        else { p = 1; q = 1; }                 // 'T' or any other (treated as T)

        long long num = n * q - m * p;   // numerator of remaining foreign amount

        if (num < 0) {
            std::cout << "No Money\n";
            continue;
        }

        // rounded value in cents (two decimal digits)
        long long scaled = (num * 100 + p / 2) / p;   // round to nearest cent

        if (scaled < 5) {                 // less than 0.05
            std::cout << c << " 0.00\n";
        } else {
            long long intPart = scaled / 100;
            long long frac    = scaled % 100;
            std::cout << c << ' ' << intPart << '.';
            if (frac < 10) std::cout << '0';
            std::cout << frac << '\n';
        }
    }
    return 0;
}
