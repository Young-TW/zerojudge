#include <iostream>

int main() {
    int num;
    int rev = 0;
    int rem;
    std::cin >> num;
    while(num > 0){
        rem = num % 10;
        rev = rev * 10 + rem;
        num /= 10;
    }

    std::cout << rev;
    return 0;
}