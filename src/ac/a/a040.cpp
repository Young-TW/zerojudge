#include <iostream>
#include <cmath>

int main() {
    int n, m;
    int digits, tt, reg;
    bool judge = 0;

    std::cin >> n >> m;

    for (int i=n; i<m; i++) {
        reg = i;
        for (digits=0; reg>0; reg/=10) {
            digits++;
        }

        reg = i;
        for (tt=0; reg>0; reg/=10) {
            tt += pow(reg%10,digits);
        }

        if (tt == i) {
            std::cout << tt << " ";
            judge = 1;
        }
    }

    if (judge == 0) {
        std::cout << "none" << std::endl;
    }

    return 0;
}