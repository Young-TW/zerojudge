// 羅馬數字
#include <iostream>
#include <string>

int romanToInt(const std::string& s) {
    auto value = [](char c) -> int {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
        }
        return 0;
    };
    int total = 0;
    for (std::size_t i = 0; i < s.size(); ++i) {
        int cur = value(s[i]);
        if (i + 1 < s.size() && cur < value(s[i + 1])) {
            total -= cur;
        } else {
            total += cur;
        }
    }
    return total;
}

std::string intToRoman(int n) {
    if (n == 0) return "ZERO";
    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    std::string result;
    for (int i = 0; i < 13; ++i) {
        while (n >= values[i]) {
            result += symbols[i];
            n -= values[i];
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string a, b;
    while (std::cin >> a) {
        if (a == "#") break;
        std::cin >> b;
        int diff = romanToInt(a) - romanToInt(b);
        if (diff < 0) diff = -diff;
        std::cout << intToRoman(diff) << '\n';
    }
    return 0;
}
