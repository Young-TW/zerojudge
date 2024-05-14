#include <iostream>
#include <vector>

int judge(int a, int b) {
    if (a == b) return 0;            // 平手
    if (a == 0 && b == 2) return 1;  // a獲勝
    if (a == 2 && b == 5) return 1;
    if (a == 5 && b == 0) return 1;
    if (b == 0 && a == 2) return 2;  // b獲勝
    if (b == 2 && a == 5) return 2;
    if (b == 5 && a == 0) return 2;
    return 0;
}

int win(int a) {
    if (a == 0) return 5;
    if (a == 2) return 0;
    if (a == 5) return 2;
    return 0;
}

int main() {
    int f, n, reg;
    std::vector<int> y;

    std::cin >> f;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> reg;
        y.push_back(reg);
    }
    y.push_back(1);
    int round = 0;
    while (1) {
        if (round > 1) {  // 妹妹連續兩次出同樣的拳
            if (y[round - 1] == y[round - 2])
                f = win(y[round - 1]);
            else
                f = y[round - 1];
        }
        std::cout << f << " ";

        switch (judge(f, y[round])) {
            case 0:
                break;
            case 1:
                std::cout << ": Won at round " << round + 1;
                break;
            case 2:
                std::cout << ": Lost at round " << round + 1;
                break;
        }

        if (judge(f, y[round]) != 0) break;

        if (y[round + 1] == 1) {
            std::cout << ": Drew at round " << round + 1;
            break;
        }

        round++;
    }
    return 0;
}