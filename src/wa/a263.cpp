#include <iostream>

int month[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

int main() {
    int y1, m1, d1, y2, m2, d2;
    int ans;
    while (std::cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2) {
        for (int i = 0; i < y1; i++) {
            if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
                d1 += 366;
            } else {
                d1 += 365;
            }
        }

        for (int i = 0; i < y2; i++) {
            if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
                d2 += 366;
            } else {
                d2 += 365;
            }
        }

        d1 += month[m1 - 1];
        d2 += month[m2 - 1];
        ans = d1 - d2;
        if (ans < 0) ans = -ans;
        std::cout << ans << std::endl;
    }

    return 0;
}

// wa line:2