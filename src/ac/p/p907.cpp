#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int s[6];
    while (std::cin >> s[0] >> s[1] >> s[2] >> s[3] >> s[4] >> s[5]) {
        for (int i = 0; i < 6; ++i) {
            int top, front, avg, back, bottom;
            std::cin >> top >> front >> avg >> back >> bottom;

            char ans;
            if (s[i] == 0) ans = 'X';          // 缺考
            else if (s[i] >= top) ans = 'A';   // 頂標
            else if (s[i] >= front) ans = 'B'; // 前標
            else if (s[i] >= avg) ans = 'C';   // 均標
            else if (s[i] >= back) ans = 'D';  // 後標
            else if (s[i] >= bottom) ans = 'E';// 底標
            else ans = 'F';                    // 低於底標

            std::cout << ans << '\n';
        }
    }
    return 0;
}
