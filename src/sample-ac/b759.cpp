#include <iostream>
#include <string>

int main() {
    std::string x;
    while (std::cin >> x) {
        std::size_t n = x.size();
        for (std::size_t i = 0; i < n; ++i) {
            std::cout << x.substr(i) << x.substr(0, i) << '\n';
        }
    }
    return 0;
}
// 我明明就有說過= =
