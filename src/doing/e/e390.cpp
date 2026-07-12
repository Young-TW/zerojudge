#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // UTF-8 encoding for the 10 "Xu Gong Gai" characters (Big5 second byte 0x5C)
    const std::unordered_set<std::string> xu_gong_gai = {
        "\xE8\xA8\xB1", // 許 U+8A31
        "\xE5\x8A\x9F", // 功 U+529F
        "\xE8\x93\x8B", // 蓋 U+84CB
        "\xE5\x97\x86", // 嗆 U+55C6
        "\xE5\xA1\x8F", // 塏 U+584F
        "\xE5\xA3\x93", // 壓 U+58D3
        "\xE7\xBD\x90", // 罐 U+7F50
        "\xE8\xB1\xB9", // 豹 U+8C79
        "\xE9\x86\x80", // 釀 U+9180
        "\xE9\xAE\xAE"  // 鮮 U+9BAE
    };

    std::string s;
    while (std::cin >> s) {
        if (xu_gong_gai.find(s) != xu_gong_gai.end()) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
    return 0;
}
