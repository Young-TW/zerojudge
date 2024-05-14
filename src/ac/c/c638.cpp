#include <iostream>
#include <string>

int main() {
    std::string t[10] = {"庚", "辛", "壬", "癸", "甲", "乙", "丙", "丁", "戊", "己"};
    std::string d[12] = {"申", "酉", "戌", "亥", "子", "丑",
                    "寅", "卯", "辰", "巳", "午", "未"};
    int n;
    while (std::cin >> n) {
        std::cout << t[n % 10] << d[n % 12] << std::endl;
    }
    return 0;
}