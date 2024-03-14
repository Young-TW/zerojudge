#include <iostream>
#include <algorithm>

int main() {
    int n, d, tt = 0, count = 0;
    int price[3];
    std::cin >> n >> d;
    for (int i=0; i<n; i++) {
        for (int j=0; j<3; j++) {
            std::cin >> price[j];
        }

        std::sort(price, price + 3);
        if (price[2] - price[0] > d) {
            tt += (price[0] + price[1] + price[2]) / 3;
            count++;
        }
    }

    std::cout << count << " " << tt;
    return 0;
}