#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    while (std::getline(std::cin, s)) {
        if (!s.empty() && s.back() == '\r') {
            s.pop_back();
        }
        for (int k = 0; k <= 25; ++k) {
            std::string decrypted = s;
            for (char &c : decrypted) {
                if (c >= 'A' && c <= 'Z') {
                    c = ((c - 'A' + k) % 26) + 'A';
                } else if (c >= 'a' && c <= 'z') {
                    c = ((c - 'a' + k) % 26) + 'a';
                }
            }
            if (decrypted.find("Love") != std::string::npos || decrypted.find("love") != std::string::npos) {
                std::cout << k << "\n";
                break;
            }
        }
    }
    return 0;
}
