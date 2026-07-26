#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::vector<std::string> zodiac = {
        "鼠", "牛", "虎", "兔", "龍", "蛇",
        "馬", "羊", "猴", "雞", "狗", "豬"
    };

    long long y;
    while (std::cin >> y) {
        int idx;
        if (y > 0) {
            idx = static_cast<int>((y - 1) % 12);
        } else {                // y < 0, year 0 does not exist
            int m = static_cast<int>((-y) % 12);
            idx = (12 - m) % 12;
        }
        std::cout << zodiac[idx] << '\n';
    }
    return 0;
}
