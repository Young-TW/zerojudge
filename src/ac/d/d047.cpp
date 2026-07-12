#include <iostream>
#include <string>

int mod(const std::string& s, int m) {
    int res = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        res = (res * 10 + (s[i] - '0')) % m;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string year;
    bool first = true;
    
    while (std::cin >> year) {
        if (!first) {
            std::cout << "\n";
        }
        first = false;
        
        int mod4 = mod(year, 4);
        int mod100 = mod(year, 100);
        int mod400 = mod(year, 400);
        int mod15 = mod(year, 15);
        int mod55 = mod(year, 55);
        
        bool is_leap = (mod4 == 0 && mod100 != 0) || (mod400 == 0);
        bool is_hulu = (mod15 == 0);
        bool is_bulu = (mod55 == 0 && is_leap);
        bool is_ordinary = !is_leap && !is_hulu && !is_bulu;
        
        if (is_leap) {
            std::cout << "This is leap year.\n";
        }
        if (is_hulu) {
            std::cout << "This is huluculu festival year.\n";
        }
        if (is_bulu) {
            std::cout << "This is bulukulu festival year.\n";
        }
        if (is_ordinary) {
            std::cout << "This is an ordinary year.\n";
        }
    }
    
    return 0;
}
