#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s1, s2, s3;
    if (!(std::cin >> s1 >> s2 >> s3)) return 0;   // no input

    std::cout << s2 << '\n' << s3 << '\n' << s1 << '\n';
    return 0;
}
