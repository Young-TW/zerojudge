#include <cmath>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    while (n--) {
        long long x, y;
        std::cin >> x >> y;
        long long yee = 100 - (std::llabs(x) + std::llabs(y));
        if (yee > 0 && yee <= 30) {
            std::cout << "sad!\n";
        } else if (yee > 30 && yee <= 60) {
            std::cout << "hmm~~\n";
        } else if (yee > 60 && yee < 100) {
            std::cout << "Happyyummy\n";
        } else {
            std::cout << "evil!!\n";
        }
    }
    return 0;
}
// 電腦教室的傑克
