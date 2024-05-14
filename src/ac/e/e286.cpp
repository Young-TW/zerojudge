#include <iostream>

int main() {
    int sum1, sum2, point1 = 0, point2 = 0;
    int input;
    for (int k = 0; k < 2; k++) {
        sum1 = 0;
        sum2 = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                std::cin >> input;
                if (i == 0) {
                    sum1 += input;
                } else {
                    sum2 += input;
                }
            }
        }
        std::cout << sum1 << ":" << sum2 << std::endl;
        if (sum1 > sum2) {
            point1++;
        } else {
            point2++;
        }
    }
    if (point1 > point2) {
        std::cout << "Win";
    } else if (point1 == point2) {
        std::cout << "Tie";
    } else {
        std::cout << "Lose";
    }
    return 0;
}