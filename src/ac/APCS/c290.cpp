#include <iostream>
#include <string>

int main() {
    int a = 0, b = 0;
    std::string n;
    std::cin >> n;
    for (int i=0; i<n.length(); i++) {
        if (i%2 == 0) a += n[i] - '0';
        else b += n[i] - '0';
    }

    a = a-b;
    if (a < 0) a = a*-1;
    std::cout << a;
    return 0;
}