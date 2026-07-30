// c092. UVa 587 藏寶圖 — 8 方位累加位移,輸出終點座標與距離。
// 修正:剝除 \r(CRLF 輸入時 "END\r"≠"END" 會被當額外地圖 → OLE/WA);防 -0.000。
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cctype>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const double diag = std::sqrt(2.0) / 2.0;
    std::string line;
    int mapNo = 1;

    while (std::getline(std::cin, line)) {
        // 剝除結尾 \r 與空白
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n' || line.back() == ' '))
            line.pop_back();
        if (line == "END") break;
        if (line.empty()) continue;

        double x = 0.0, y = 0.0;
        std::size_t i = 0;
        while (i < line.size()) {
            long long dist = 0;
            while (i < line.size() && std::isdigit((unsigned char)line[i])) {
                dist = dist * 10 + (line[i] - '0');
                ++i;
            }
            std::string dir;
            while (i < line.size() && std::isalpha((unsigned char)line[i])) {
                dir.push_back(line[i]);
                ++i;
            }
            if (dir == "N")       { y += dist; }
            else if (dir == "S")  { y -= dist; }
            else if (dir == "E")  { x += dist; }
            else if (dir == "W")  { x -= dist; }
            else if (dir == "NE") { x += dist * diag; y += dist * diag; }
            else if (dir == "NW") { x -= dist * diag; y += dist * diag; }
            else if (dir == "SE") { x += dist * diag; y -= dist * diag; }
            else if (dir == "SW") { x -= dist * diag; y -= dist * diag; }

            if (i < line.size()) {
                if (line[i] == '.') break;   // 本圖結束
                ++i;                         // 跳過逗號
            }
        }

        double d = std::sqrt(x * x + y * y);
        if (std::fabs(x) < 5e-4) x = 0.0;   // 防 -0.000
        if (std::fabs(y) < 5e-4) y = 0.0;

        if (mapNo > 1) std::cout << "\n";    // 地圖間空一行,末圖後不留多餘空行
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Map #" << mapNo << "\n";
        std::cout << "The treasure is located at (" << x << "," << y << ").\n";
        std::cout << "The distance to the treasure is " << d << ".\n";
        ++mapNo;
    }
    return 0;
}
