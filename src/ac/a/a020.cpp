#include <iostream>
#include <string>

int main() {
    int a[26] ={
        1, 10, 19, 28, 37,
        46, 55, 64, 39, 73,
        82, 2, 11, 20, 48,
        29, 38, 47, 56, 65,
        74, 83, 21, 3, 12,
        30
    };

    std::string s;
    std::cin >> s;
    int tt = a[s[0] - 'A'];
    for(int i=1; i<s.length(); i++)
        tt += (s[i] - '0') * (9 - i);

    tt += s[9] - '0';
    if (tt%10==0)
        std::cout << "real" << std::endl;
    else
        std::cout << "fake" << std::endl;
    return 0;
}