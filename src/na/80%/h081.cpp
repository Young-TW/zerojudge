#include <iostream>

int main() {
    int n, d, x, tt = 0;
    bool status;
    std::cin >> n >> d;
    int y[n];
    for (int i=0; i<n; i++) {
        std::cin >> y[i];
        if (i == 0) {
            x = y[i];
            status = 1;
        }

        if (y[i] >= x+d && status) {
            tt += y[i] - x;
            status = 0;
        }
        if (y[i] <= x-d && !status) {
            x = y[i];
            status = 1;
        }
    }

    std::cout << tt << std::endl;
    return 0;
}