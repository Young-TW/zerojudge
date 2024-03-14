#include <iostream>

int main() {
    int n;
    std::cin >> n;
    bool judge = 0;
    for(int i=2; i<n/2; i++){
        if (n%i == 0) {
            judge = 1;
            break;
        }
    }

    if (judge) {
        std::cout << "no";
        return 0;
    }

    std::cout << "yes";
    return 0;
}