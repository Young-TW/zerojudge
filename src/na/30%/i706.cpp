#include <iostream>
#include <vector>

int main() {
    int n, flag;
    std::cin >> n;
    std::vector<int> h(n);
    for (int i=0; i<n; i++) {
        std::cin >> h[i];
    }

    for (int i=0; i<n; i++) {
        flag = i;
        while (flag >= 0 && h[i] <= h[flag]) {
            --flag;
        }

        if (flag >= 0) {
            std::cout << flag + 1 << " ";
        } else {
            std::cout << "0 ";
            continue;
        }
    }

    return 0;
}